#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Character.h"

namespace Player
{
    enum struct PState
    {
        IDLE_GR = 0,  //待機_接地
        IDLE_FL,      //待機_滞空
        WALK_GR,      //歩行_接地
        MOVE_FL,      //移動_滞空
        DEPLOY_GR,    //展開_接地
        DEPLOY_FL,    //展開_滞空
    };

    const std::string   def_task  ("プレイヤー");   //タスク名
    
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
        std::shared_ptr<Resource> res_;  //確保したリソース

        ImageDrawer player_image_;  //プレイヤー画像
        Character player_;          //プレイヤーキャラクター情報
        PState state_;              //プレイヤーの状態

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

        Math::Vec2 GetCenterPos();  //座標取得
        bool GetIsTurn();           //画像が反転されているか否かを取得(反転されていたらtrue)

    private:
        //状態に応じた処理と移動方向の取得
        Math::Vec2 InputToGetMovingDirection();
        //状態遷移
        void StateTransition(const Math::Vec2& velocity);

        //状態の変更
        void SetPlayerState(PState state, bool is_reset_time = true);
    };
}