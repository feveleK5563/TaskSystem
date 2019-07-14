#pragma once
#include <array>
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "MLine.h"

namespace Mudra
{
    const std::string   def_task  ("イン");        //タスク名

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
        std::shared_ptr<Resource> res_; //確保したリソース
        float ratio_;   //拡大率

        bool is_active_;
        bool release_;
        Math::Vec2 pos_;
        ImageDrawer mudra_image_;

        std::array<Math::Box2D, 4> mudra_rect_;
        int before_box_num_;
        int now_box_num_;

        MLine mline_;

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
        void Draw() override;       //描画

        //描画された線を取得
        int GetMLine();
        //動作状態を取得
        bool IsActive();

    private:
        //座標の設定
        void SetPos(const Math::Vec2& pos);
        //印接触位置との接触判定
        void HitMudraPoint(const Math::Box2D& rect);
    };
}