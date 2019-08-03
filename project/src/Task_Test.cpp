#include "Task_Test.h"
#include "ImageLoader.h"

namespace Test
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    // リソースのコンストラクタ
    Resource::Resource()
    {
        ImageLoader::LoadOneImage("test", "data/image/test.png");
    }
    //----------------------------------------------
    // リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData("test");
    }
    //----------------------------------------------
    // リソースの生成
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
    // タスクのコンストラクタ
    Task::Task():
        TaskAbstract(task_name, 0.f),
        res_(Resource::Create())
    {
    }
    //----------------------------------------------
    // タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    // タスクの生成
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
    // 初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
        drawer.Initialize("test", Math::BoxCP::CENTER);
    }

    //----------------------------------------------
    // 終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    // 更新
    //----------------------------------------------
    void Task::Update()
    {
    }

    //----------------------------------------------
    // 描画
    //----------------------------------------------
    void Task::Draw()
    {
        drawer.Draw(Math::Vec2(100, 100));
    }
}