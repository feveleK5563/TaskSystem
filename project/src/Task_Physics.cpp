#include "Task_Physics.h"

namespace Physics
{
    //----------------------------------------------
    // タスクのコンストラクタ
    Task::Task()
        : TaskAbstract(task_name, 0.f)
        , angle_(0.f)
        , angle_velocity_(0.f)
        , angle_acceleration_(0.f)
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
        return task;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    // 初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
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
        position_ += velocity_;
        velocity_ += acceleration_;

        angle_ += angle_velocity_;
        angle_velocity_ += angle_acceleration_;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    // 座標設定
    void Task::SetPos(const Math::Vec2& position)
    {
        position_ = position;
    }
    //----------------------------------------------
    // 速度設定
    void Task::SetVel(const Math::Vec2& velocity)
    {
        velocity_ = velocity;
    }
    //----------------------------------------------
    // 加速度設定
    void Task::SetAcc(const Math::Vec2& acceleration)
    {
        acceleration_ = acceleration;
    }
    //----------------------------------------------
    // 角度設定
    void Task::SetAng(float angle)
    {
        angle_ = angle;
    }
    //----------------------------------------------
    // 角速度設定
    void Task::SetAngVel(float angle_velocity)
    {
        angle_velocity_ = angle_velocity;
    }
    //----------------------------------------------
    // 角加速度設定
    void Task::SetAngAcc(float angle_acceleration)
    {
        angle_acceleration_ = angle_acceleration;
    }

    //----------------------------------------------
    // 座標取得
    const Math::Vec2& Task::GetPos()
    {
        return position_;
    }
    //----------------------------------------------
    // 角度設定
    const float& Task::GetAng()
    {
        return angle_;
    }
}