#include "Task_BackGround.h"
#include "ImageLoader.h"
#include "TaskDefData.h"

namespace BackGround
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //リソースのコンストラクタ
    Resource::Resource()
    {
        back_image_ = "back";
        ImageLoader::LoadOneImage(back_image_, "data/image/back.png");
    }
    //----------------------------------------------
    //リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData(back_image_);
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
        res_(Resource::Create())
    {
        SetPriority(Priority::BACK);
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
        back_.Initialize(res_->back_image_, Math::BoxCP::TOP_LEFT);
        back_.SetScale(Ratio::layer_main);
    }

    //----------------------------------------------
    //終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    //描画
    //----------------------------------------------
    void Task::Draw()
    {
        back_.Draw(Math::Vec2(0, 0));
    }
}