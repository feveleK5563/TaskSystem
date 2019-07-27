#include "Task_Player.h"
#include "TaskDefData.h"
#include "ImageLoader.h"
#include "PadInputConfig.h"
#include "SystemDefine.h"
#include "Task_Map.h"
#include "Task_Camera.h"
#include "Task_Mudra.h"
#include "Utility.h"

namespace Player
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //リソースのコンストラクタ
    Resource::Resource()
    {
        image_name_ = "sayori";

        ImageLoader::LoadDivImage(image_name_, "data/image/sayori.png", 36, 6, 6, 32, 32);

        //---アニメーション---
        ImageLoader::AddAnimationData(image_name_,  0,  5,  8.f, true);  //00-待機_接地(IDLE_GR)
        ImageLoader::AddAnimationData(image_name_,  6, 11, 10.f, true);  //01-待機_滞空(IDLE_FL)

        ImageLoader::AddAnimationData(image_name_, 12, 16,  5.f, true);  //02-歩行_接地(WALK_GR)
        ImageLoader::AddAnimationData(image_name_, 18, 22,  8.f, true);  //03-移動_滞空(MOVE_FL)

        ImageLoader::AddAnimationData(image_name_, 24, 29, 12.f, true);  //04-展開_接地(DEPLOY_GR)
        ImageLoader::AddAnimationData(image_name_, 30, 35, 15.f, true);  //05-展開_滞空(DEPLOY_FL)
    }
    //----------------------------------------------
    //リソースのデストラクタ
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData(image_name_);
    }
    //----------------------------------------------
    //リソースの生成
    std::shared_ptr<Resource> Resource::Create()
    {
        auto sp = instance_.lock();
        if (!sp)
        {
            sp = std::make_shared<Resource>();
            instance_ = sp;
        }
        return sp;
    }

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    //★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

    //----------------------------------------------
    //タスクのコンストラクタ
    Task::Task():
        TaskAbstract(def_task),
        res_(Resource::Create()),
        state_(PState::IDLE_GR)
    {
        SetPriority(Priority::PLAYER);
    }
    //----------------------------------------------
    //タスクのデストラクタ
    Task::~Task()
    {
    }
    //----------------------------------------------
    //タスクの生成
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
    //◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

    //----------------------------------------------
    //初期化処理
    //----------------------------------------------
    void Task::Initialize()
    {
        player_image_.Initialize(res_->image_name_, Math::BoxCP::BOTTOM_MIDDLE);
        player_image_.SetScale(Ratio::layer_main);
        player_image_.SetTurnFlag(false);
        player_image_.ChangeAnimPattern(0, true);

        player_.SetBoxCP(Math::BoxCP::BOTTOM_MIDDLE);
        player_.SetPos(Math::Vec2(250, 200));
        player_.SetLandRect(Math::Box2D(0, 0, 22, 54));
        player_.SetVelocity(6.f);
        player_.SetIsVelConstant(true);
        player_.SetIsGravity(true);
    }

    //----------------------------------------------
    //終了処理
    //----------------------------------------------
    void Task::Finalize()
    {
    
    }

    //----------------------------------------------
    //更新
    //----------------------------------------------
    void Task::Update()
    {
        Math::Vec2 velocity(InputToGetMovingDirection());
        StateTransition(velocity);

        player_image_.AnimUpdate();
        player_.AutoRevitionMove(velocity);

        auto cam = TaskSystem::GetTaskOne<Camera::Task>(Camera::def_task);
        cam->SetTargetPos(player_.GetCenterPos() - 
            Math::Vec2(SysDef::SizeX / 2.f, SysDef::SizeY * 2.f / 3.f));
    }

    //----------------------------------------------
    //描画
    //----------------------------------------------
    void Task::Draw()
    {
        auto mudra = TaskSystem::GetTaskOne<Mudra::Task>(Mudra::def_task);
        if (mudra && mudra->IsActive())
        {
            player_image_.DrawSilhouette(player_.GetPosForCam(false), Color(255, 100, 100));
        }
        else
        {
            player_image_.Draw(player_.GetPosForCam(false));
        }

        //player_.DrawRect(false, GetColor(255, 255, 255), true);
    }

    //----------------------------------------------
    //座標取得
    Math::Vec2 Task::GetCenterPos()
    {
        return player_.GetCenterPos();
    }

    //----------------------------------------------
    //画像が反転されているか(反転されていたらtrue)
    bool Task::GetIsTurn()
    {
        return player_image_.GetIsTurn();
    }

    //----------------------------------------------
    //状態に応じた処理と移動方向の取得
    Math::Vec2 Task::InputToGetMovingDirection()
    {
        Math::Vec2 velocity;
        auto& input = PadInputConfig::Get(0);

        //入力情報を取得
        velocity = input.GetVecStickL();
        //入力無効範囲(0.3f)
        if (fabsf(velocity.x) < 0.3f) { velocity.x = 0.f; }
        if (fabsf(velocity.y) < 0.3f) { velocity.y = 0.f; }

        //展開状態だったら移動速度低減
        if (state_ == PState::DEPLOY_GR ||
            state_ == PState::DEPLOY_FL)
        {
            velocity *= 0.f;
        }
        else
        {
            //向き反転
            if (velocity.x < 0.f) { player_image_.SetTurnFlag(true); }
            else if (velocity.x > 0.f) { player_image_.SetTurnFlag(false); }
        }

        //接地状態の処理
        if (player_.IsGround())
        {
            player_.SetIsVelConstant(true);
            player_.SetIsGravity(true);
        }

        //重力有効状態の処理
        if (player_.IsGravity())
        {
            if (velocity.y < 0.f)
            {
                player_.SetIsVelConstant(false);
                player_.SetIsGravity(false);
            }
        }

        return velocity;
    }

    //----------------------------------------------
    //状態遷移
    void Task::StateTransition(const Math::Vec2& velocity)
    {
        auto& input = PadInputConfig::Get(0);
        switch (state_)
        {
        case PState::IDLE_GR:   //接地待機
            //移動し始めたら接地歩行
            if (velocity.x != 0.f) { SetPlayerState(PState::WALK_GR); }
            //上に移動したら浮遊移動
            if (velocity.y < 0.f) { SetPlayerState(PState::MOVE_FL); }
            //Rを押したら接地展開
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_GR, false);
            }
            break;

        case PState::IDLE_FL:   //浮遊待機
            //移動し始めたら浮遊歩行
            if (velocity.GetDistance() > 0.f) { SetPlayerState(PState::MOVE_FL); }
            //Rを押したら浮遊展開
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_FL, false);
            }
            break;

        case PState::WALK_GR:   //接地歩行
            //移動していない場合は接地待機
            if (velocity.x == 0.f) { SetPlayerState(PState::IDLE_GR); }
            //上に移動したら浮遊移動
            if (velocity.y < 0.f) { SetPlayerState(PState::MOVE_FL); }
            //Rを押したら接地展開
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_GR);
            }
            break;

        case PState::MOVE_FL:   //浮遊移動
            //移動していない場合は接地待機
            if (velocity.GetDistance() == 0.f) { SetPlayerState(PState::IDLE_FL); }
            //接地したら接地歩行
            if (player_.IsGround()) { SetPlayerState(PState::WALK_GR); }
            //Rを押したら浮遊展開
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_FL);
            }
            break;

        case PState::DEPLOY_GR: //接地展開
            //Rを離したら接地展開解除
            if (input.GetState(PAD_INPUT::R1) != ON)
            {
                if (velocity.GetDistance() > 0.f)
                {
                    SetPlayerState(PState::WALK_GR);
                }
                else
                {
                    SetPlayerState(PState::IDLE_GR, false);
                }
            }
            break;

        case PState::DEPLOY_FL: //浮遊展開
            //Rを離したら浮遊展開解除
            if (input.GetState(PAD_INPUT::R1) != ON)
            {
                if (velocity.GetDistance() > 0.f)
                {
                    SetPlayerState(PState::MOVE_FL);
                }
                else
                {
                    SetPlayerState(PState::IDLE_FL, false);
                }
            }
            break;
        }
    }

    //----------------------------------------------
    //状態の変更
    void Task::SetPlayerState(PState state, bool is_reset_time)
    {
        if (state_ == state)
        {
            return;
        }

        state_ = state;
        player_image_.ChangeAnimPattern((int)state, is_reset_time);
    }
}