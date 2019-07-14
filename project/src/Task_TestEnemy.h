#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Character.h"
#include "ImageDrawer.h"
#include "Task_EnemyKata.h"

namespace TestEnemy
{
    const std::string   def_task  ("敵テスト");      //タスク名

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;

    public:
        std::string image_name_;

        Resource();     //コンストラクタ
        ~Resource();    //デストラクタ
        static std::shared_ptr<Resource> Create();  //リソースの生成
    };

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;	//確保したリソース

        ImageDrawer enemy_image_;
        Character enemy_;

        std::shared_ptr<EnemyKata::Task> kata;

    public:
        //コンストラクタ
        Task(const Math::Vec2& pos);
        
        //デストラクタ
        ~Task();
        
        //タスクの生成
        static std::shared_ptr<Task> Create(const Math::Vec2& pos);

        void Initialize();          //初期化処理
        void Finalize() override;   //終了処理
        void Update() override;     //更新
        void Draw() override;       //描画
    };
}