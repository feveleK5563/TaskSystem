#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "MLine.h"

namespace EnemyKata
{
    const std::string   def_task  ("EnemyKata");   //タスク名

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        Math::Vec2 pos_;
        MLine mline_;

    public:
        //コンストラクタ
        Task(float dist, int thick, int max_line, int min_line);

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create(float dist, int thick, int max_line, int min_line);

        void Initialize() override; //初期化処理
        void Finalize() override;   //終了処理
        void Draw() override;       //描画

        void SetDrawPos(const Math::Vec2& pos);
        MLine::MHit GetHitState();  //Mudraとの判定結果を取得する
    };
}