#pragma once
#include "DxLib.h"
#include "Math.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Camera
{
    const std::string   def_task  ("カメラ"); //タスク名

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        float speed_;
        Math::Vec2 pos_;
        Math::Vec2 velocity_;
        Math::Box2D camera_rect_;

    public:
        //コンストラクタ
        Task();

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create();

        void Initialize();          //初期化処理
        void Finalize() override;   //終了処理
        void Update() override;     //更新

        void SetTargetPos(const Math::Vec2& target);        //目標となる座標を設定
        Math::Vec2 GetScreenPos(const Math::Vec2& target);  //座標をカメラ準拠にして返す
    };
}