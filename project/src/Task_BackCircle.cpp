#include "Task_BackCircle.h"
#include "ShaderManager.h"
#include "SystemDefine.h"
#include "TaskDefData.h"

namespace BackCircle
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //リソースのコンストラクタ
    Resource::Resource()
    {
        shader_name = "circleShader";
        ShaderManager::LoadShader(shader_name, "data/shader/circle.pso");
        buffer_name = "circleBuffer";
        ShaderManager::CreateConstantBuffer<CircleInfo>(buffer_name);
    }
    //----------------------------------------------
    //リソースのデストラクタ
    Resource::~Resource()
    {
        ShaderManager::DeleteShaderData(shader_name);
        ShaderManager::DeleteConstantBuffer(buffer_name);
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
    Task::Task(const Color& color):
        TaskAbstract(def_task),
        res_(Resource::Create()),
        counter_(SPREAD_SPEED_, 0.f, SPREAD_SPEED_ * 60.f)
    {
        info_.window_size.u = SysDef::SizeX;
        info_.window_size.v = SysDef::SizeY;
        info_.r = color.Fr();
        info_.g = color.Fg();
        info_.b = color.Fb();
        info_.a = color.Fa();

        counter_.SetNowMax();

        SetPriority(Priority::CIRCLE);
    }
    //----------------------------------------------
    //タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    //タスクの生成
    std::shared_ptr<Task> Task::Create(const Color& color)
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>(color);
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
        counter_.Run();
        info_.radius = counter_.GetNow();
    }

    //----------------------------------------------
    //描画
    //----------------------------------------------
    void Task::Draw()
    {
        //ピクセルシェーダー用の定数バッファのアドレスを取得
        auto& cb = ShaderManager::GetConstantBuffer<CircleInfo>(res_->buffer_name);

        //各値を書き込み
        cb.window_size = info_.window_size;
        cb.center_pos = info_.center_pos;
        cb.radius = info_.radius;
        cb.color_flag = info_.color_flag;
        cb.r = info_.r;
        cb.g = info_.g;
        cb.b = info_.b;
        cb.a = info_.a;

        ShaderManager::DrawShader(res_->shader_name, res_->buffer_name);
    }

    //----------------------------------------------
    //着色フラグ設定
    void Task::SetColorFlag(bool color_flag)
    {
        info_.color_flag = color_flag;
        counter_.Reset();
        info_.radius = 0.f;
    }

    //----------------------------------------------
    //座標設定
    void Task::SetPos(const Math::Vec2& pos)
    {
        info_.center_pos.u = pos.x;
        info_.center_pos.v = pos.y;
    }
}