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
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        image_name_ = "mudra";

        auto& imgl = ImageLoader::GetInstance();
        imgl.LoadOneImage(image_name_, "data/image/mudra.png");
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ImageLoader::GetInstance().DeleteImageData(image_name_);
    }
    //----------------------------------------------
    //���\�[�X�̐���
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

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
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
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task = 
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //����������
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
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //�X�V
    //----------------------------------------------
    void Task::Update()
    {
        auto jouetsu = TaskSystem::GetTaskOne<Jouetsu::Task>(Jouetsu::def_task);
        if (!is_active_)
        {
            if (!release_)
            {
                //�o��������u�����ăf�J���Ȃ�
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
                // �߂�����L�����ď�����
                ratio_ += 3.f;
                if (ratio_ > 100.f)
                {
                    SetTaskState(TaskState::Kill);
                }
            }
        }
        else
        {
            //�T�C�Y���ő�ɂȂ�����W���E�G�c����ƐڐG������s��
            HitMudraPoint(jouetsu->GetRect());

            //R�{�^���𗣂�����L����
            if (PadInputConfig::GetInstance(0).GetState(PAD_INPUT::R1) != ON)
            {
                is_active_ = false;
                release_ = true;
            }
        }
        mudra_image_.SetScale(ratio_);
    }

    //----------------------------------------------
    //�`��
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
    //�`�悳�ꂽ�����擾
    int Task::GetMLine()
    {
        if (GetTaskState() != TaskState::Kill)
        {
            return 0;
        }
        return mline_.GetMLine();
    }

    //----------------------------------------------
    //�����Ԃ��擾
    bool Task::IsActive()
    {
        return is_active_;
    }

    //----------------------------------------------
    //���W�̐ݒ�
    void Task::SetPos(const Math::Vec2& pos)
    {
        pos_ = pos;
        mudra_rect_[0].SetPos(pos_ + Math::Vec2(0.f, -48.f * Ratio::layer_main), Math::BoxCP::CENTER);
        mudra_rect_[1].SetPos(pos_ + Math::Vec2(-48.f * Ratio::layer_main, 0.f), Math::BoxCP::CENTER);
        mudra_rect_[2].SetPos(pos_ + Math::Vec2(48.f * Ratio::layer_main, 0.f), Math::BoxCP::CENTER);
        mudra_rect_[3].SetPos(pos_ + Math::Vec2(0.f, 48.f * Ratio::layer_main), Math::BoxCP::CENTER);
    }

    //----------------------------------------------
    //��ڐG�ʒu�Ƃ̐ڐG����
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