#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Math.h"

namespace Physics
{
    const std::string   task_name("Physics");   // タスク名
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        Math::Vec2 position_;       // 座標
        Math::Vec2 velocity_;       // 速度
        Math::Vec2 acceleration_;   // 加速度
        float angle_;               // 角度
        float angle_velocity_;      // 角速度
        float angle_acceleration_;  // 角加速度

    public:
        //コンストラクタ
        Task();

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create();

        void Initialize() override; // 初期化処理
        void Finalize() override;   // 終了処理
        void Update() override;     // 更新

        void SetPos(const Math::Vec2& position);        // 座標設定
        void SetVel(const Math::Vec2& velocity);        // 速度設定
        void SetAcc(const Math::Vec2& acceleration);    // 加速度設定
        void SetAng(float angle);                       // 角度
        void SetAngVel(float angle_velocity);           // 角速度
        void SetAngAcc(float angle_acceleration);       // 角加速度

        const Math::Vec2& GetPos(); // 座標取得
        const float& GetAng();      // 角度取得
    };
    using TaskPtr = std::shared_ptr<Task>;
}