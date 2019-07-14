#pragma once
#include "DxLib.h"
#include "TaskSystem.h"

namespace タスク名
{
    const std::string   def_group (グループ名); //グループ名
    const std::string   def_task  (タスク名);   //タスク名
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
    
        Resource();     //コンストラクタ
        ~Resource();    //デストラクタ
        static std::shared_ptr<Resource> Create();  //リソースの生成
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  //確保したリソース

    public:
        //コンストラクタ
        Task();

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create();

        void Initialize() override; //初期化処理
        void Finalize() override;   //終了処理
        void Update() override;     //更新
        void Draw() override;       //描画
    };
}