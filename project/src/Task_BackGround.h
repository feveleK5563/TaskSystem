#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace BackGround
{
    const std::string   def_task  ("背景1");       //タスク名
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
        std::string back_image_;
    
        Resource();     //コンストラクタ
        ~Resource();    //デストラクタ
        static std::shared_ptr<Resource> Create();  //リソースの生成
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  //確保したリソース
        ImageDrawer back_;

    public:
        //コンストラクタ
        Task();

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create();

        void Initialize() override; //初期化処理
        void Finalize() override;   //終了処理
        void Draw() override;       //描画
    };
}