#include "Task_Mudra.h"
#include "TaskDefData.h"
#include "ImageLoader.h"
#include "PadInputConfig.h"
#include "Task_Jouetsu.h"
#include "Task_Camera.h"
#include "Utility.h"

namespace Mudra
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //リソースのコンストラクタ
    Resource::Resource()
    {
        image_name_ = "mudra";

        auto& imgl = ImageLoader::GetInstance();
        imgl.LoadOneImage(image_name_, "data/image/mudra.png");
    }
    //----------------------------------------------
    //リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::GetInstance().DeleteImageData(image_name_);
    }
    //----------------------------------------------
    //リソースの生成
    std::shared_ptr<Resource> Resource::Create()
    {
        auto sp = instance_.lock();
        if (!sp)
        {
            sp = std::make_shared<Resource>();
            instance_ = sp;
        }
        return sp;
    }

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    //★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

    //----------------------------------------------
    //タスクのコンストラクタ
    Task::Task():
        TaskAbstract(def_task),
        res_(Resource::Create()),
        ratio_(0.f),
        is_active_(false),
        release_(false),
        before_box_num_(-1),
        now_box_num_(-1),
        mline_(40.f * Ratio::layer_main, 5)
    {
        SetPriority(Priority::MUDRA);
    }
    //----------------------------------------------
    //タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    //タスクの生成
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task = 
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    //初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
        mudra_image_.Initialize(res_->image_name_, Math::BoxCP::CENTER);
        mudra_image_.SetScale(ratio_);

        for (size_t i = 0u; i < mudra_rect_.size(); ++i)
        {
            mudra_rect_[i].w = 32 * Ratio::layer_main;
            mudra_rect_[i].h = 32 * Ratio::layer_main;
        }
    }

    //----------------------------------------------
    //終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //更新
    //----------------------------------------------
    void Task::Update()
    {
        auto jouetsu = TaskSystem::GetTaskOne<Jouetsu::Task>(Jouetsu::def_task);
        if (!is_active_)
        {
            if (!release_)
            {
                //出現したらブワってデカくなる
                SetPos(jouetsu->GetPivotPos());

                ratio_ += 1.f;
                if (ratio_ > Ratio::layer_main)
                {
                    is_active_ = true;
                    ratio_ = Ratio::layer_main;
                }
            }
            else
            {
                // めっちゃ広がって消える
                ratio_ += 3.f;
                if (ratio_ > 100.f)
                {
                    SetTaskState(TaskState::Kill);
                }
            }
        }
        else
        {
            //サイズが最大になったらジョウエツくんと接触判定を行う
            HitMudraPoint(jouetsu->GetRect());

            //Rボタンを離したら広がる
            if (PadInputConfig::GetInstance(0).GetState(PAD_INPUT::R1) != ON)
            {
                is_active_ = false;
                release_ = true;
            }
        }
        mudra_image_.SetScale(ratio_);
    }

    //----------------------------------------------
    //描画
    //----------------------------------------------
    void Task::Draw()
    {
        auto cam = TaskSystem::GetTaskOne<Camera::Task>(Camera::def_task);
        Math::Vec2 camPos(cam->GetScreenPos(pos_));
        mudra_image_.Draw(camPos);

        /*for (size_t i = 0; i < mudraBox.size(); ++i)
        {
            mudraBox[i].DrawRect(false);
        }*/
        mline_.Draw(camPos, Color(255, 0, 200));
    }

    //----------------------------------------------
    //描画された線を取得
    int Task::GetMLine()
    {
        if (GetTaskState() != TaskState::Kill)
        {
            return 0;
        }
        return mline_.GetMLine();
    }

    //----------------------------------------------
    //動作状態を取得
    bool Task::IsActive()
    {
        return is_active_;
    }

    //----------------------------------------------
    //座標の設定
    void Task::SetPos(const Math::Vec2& pos)
    {
        pos_ = pos;
        mudra_rect_[0].SetPos(pos_ + Math::Vec2(0.f, -48.f * Ratio::layer_main), Math::BoxCP::CENTER);
        mudra_rect_[1].SetPos(pos_ + Math::Vec2(-48.f * Ratio::layer_main, 0.f), Math::BoxCP::CENTER);
        mudra_rect_[2].SetPos(pos_ + Math::Vec2(48.f * Ratio::layer_main, 0.f), Math::BoxCP::CENTER);
        mudra_rect_[3].SetPos(pos_ + Math::Vec2(0.f, 48.f * Ratio::layer_main), Math::BoxCP::CENTER);
    }

    //----------------------------------------------
    //印接触位置との接触判定
    void Task::HitMudraPoint(const Math::Box2D& rect)
    {
        for (int i = 0; i < int(mudra_rect_.size()); ++i)
        {
            if (mudra_rect_[i].IsHit(rect))
            {
                before_box_num_ = now_box_num_;
                now_box_num_ = i;
                if ((before_box_num_ == -1) || (now_box_num_ == before_box_num_))
                {
                    break;
                }

                mline_.AddLine(before_box_num_, now_box_num_);
                break;
            }
        }
    }
}