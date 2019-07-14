#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Character.h"
#include "Task_BackCircle.h"

namespace Jouetsu
{
    const std::string   def_group ("キャラクター");   //グループ名
    const std::string   def_task  ("ジョウエツくん"); //タスク名

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

        enum class JState
        {
            Nomal,
            Jorei,
            TrJorei,
            TrNomal,
        } state_;

        ImageDrawer jouetsu_image_; //ジョウエツくん画像
        Character jouetsu_;         //情報
        Math::Vec2 pivot_pos_;      //操作基準位置
        
        std::shared_ptr<BackCircle::Task> circle_;  //円形のブワッ

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

        const Math::Vec2& GetPivotPos();    //中心座標を取得
        Math::Box2D GetRect();              //当たり判定を取得

    private:
        void InputToStateTransition();
        Math::Vec2 Move();
    };
}