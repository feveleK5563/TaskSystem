#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Math.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

namespace BackCircle
{
    const std::string   def_task  ("除霊フィールドの円形");   //タスク名

    //----------------------------------------------
    //シェーダーに送る情報
    struct CircleInfo
    {
        FLOAT2 window_size; //画面サイズ
        FLOAT2 center_pos;  //中心座標
        float radius;       //半径
        bool color_flag;    //着色フラグ
        float   r;
        float   g;
        float   b;
        float   a;

        CircleInfo():
            window_size({0.f, 0.f}),
            center_pos({0.f, 0.f}),
            radius(0.f),
            color_flag(false),
            r(0.f), g(0.f), b(0.f), a(0.f) {}
    };

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
        std::string shader_name;
        std::string buffer_name;
    
        Resource();     //コンストラクタ
        ~Resource();    //デストラクタ
        static std::shared_ptr<Resource> Create();  //リソースの生成
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        const float SPREAD_SPEED_ = 90.f;

        std::shared_ptr<Resource> res_;  //確保したリソース

        CircleInfo info_;
        Counter<float> counter_;    //半径サイズの変化

    public:
        //コンストラクタ
        Task(const Color& color);

        //デストラクタ
        ~Task();

        //タスクの生成
        static std::shared_ptr<Task> Create(const Color& color);

        void Initialize() override; //初期化処理
        void Finalize() override;   //終了処理
        void Update() override;     //更新
        void Draw() override;       //描画

        //着色フラグ設定
        void SetColorFlag(bool color_flag);

        //座標設定
        void SetPos(const Math::Vec2& pos);
    };
}