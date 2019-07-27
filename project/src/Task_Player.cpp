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
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        image_name_ = "sayori";

        ImageLoader::LoadDivImage(image_name_, "data/image/sayori.png", 36, 6, 6, 32, 32);

        //---�A�j���[�V����---
        ImageLoader::AddAnimationData(image_name_,  0,  5,  8.f, true);  //00-�ҋ@_�ڒn(IDLE_GR)
        ImageLoader::AddAnimationData(image_name_,  6, 11, 10.f, true);  //01-�ҋ@_�؋�(IDLE_FL)

        ImageLoader::AddAnimationData(image_name_, 12, 16,  5.f, true);  //02-���s_�ڒn(WALK_GR)
        ImageLoader::AddAnimationData(image_name_, 18, 22,  8.f, true);  //03-�ړ�_�؋�(MOVE_FL)

        ImageLoader::AddAnimationData(image_name_, 24, 29, 12.f, true);  //04-�W�J_�ڒn(DEPLOY_GR)
        ImageLoader::AddAnimationData(image_name_, 30, 35, 15.f, true);  //05-�W�J_�؋�(DEPLOY_FL)
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData(image_name_);
    }
    //----------------------------------------------
    //���\�[�X�̐���
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

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
    Task::Task():
        TaskAbstract(def_task),
        res_(Resource::Create()),
        state_(PState::IDLE_GR)
    {
        SetPriority(Priority::PLAYER);
    }
    //----------------------------------------------
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create()
    {
        std::shared_ptr<Task> task =
            std::make_shared<Task>();
        TaskSystem::AddTask(task);

        task->Initialize();
        return task;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    //����������
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
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
    
    }

    //----------------------------------------------
    //�X�V
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
    //�`��
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
    //���W�擾
    Math::Vec2 Task::GetCenterPos()
    {
        return player_.GetCenterPos();
    }

    //----------------------------------------------
    //�摜�����]����Ă��邩(���]����Ă�����true)
    bool Task::GetIsTurn()
    {
        return player_image_.GetIsTurn();
    }

    //----------------------------------------------
    //��Ԃɉ����������ƈړ������̎擾
    Math::Vec2 Task::InputToGetMovingDirection()
    {
        Math::Vec2 velocity;
        auto& input = PadInputConfig::Get(0);

        //���͏����擾
        velocity = input.GetVecStickL();
        //���͖����͈�(0.3f)
        if (fabsf(velocity.x) < 0.3f) { velocity.x = 0.f; }
        if (fabsf(velocity.y) < 0.3f) { velocity.y = 0.f; }

        //�W�J��Ԃ�������ړ����x�ጸ
        if (state_ == PState::DEPLOY_GR ||
            state_ == PState::DEPLOY_FL)
        {
            velocity *= 0.f;
        }
        else
        {
            //�������]
            if (velocity.x < 0.f) { player_image_.SetTurnFlag(true); }
            else if (velocity.x > 0.f) { player_image_.SetTurnFlag(false); }
        }

        //�ڒn��Ԃ̏���
        if (player_.IsGround())
        {
            player_.SetIsVelConstant(true);
            player_.SetIsGravity(true);
        }

        //�d�͗L����Ԃ̏���
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
    //��ԑJ��
    void Task::StateTransition(const Math::Vec2& velocity)
    {
        auto& input = PadInputConfig::Get(0);
        switch (state_)
        {
        case PState::IDLE_GR:   //�ڒn�ҋ@
            //�ړ����n�߂���ڒn���s
            if (velocity.x != 0.f) { SetPlayerState(PState::WALK_GR); }
            //��Ɉړ������畂�V�ړ�
            if (velocity.y < 0.f) { SetPlayerState(PState::MOVE_FL); }
            //R����������ڒn�W�J
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_GR, false);
            }
            break;

        case PState::IDLE_FL:   //���V�ҋ@
            //�ړ����n�߂��畂�V���s
            if (velocity.GetDistance() > 0.f) { SetPlayerState(PState::MOVE_FL); }
            //R���������畂�V�W�J
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_FL, false);
            }
            break;

        case PState::WALK_GR:   //�ڒn���s
            //�ړ����Ă��Ȃ��ꍇ�͐ڒn�ҋ@
            if (velocity.x == 0.f) { SetPlayerState(PState::IDLE_GR); }
            //��Ɉړ������畂�V�ړ�
            if (velocity.y < 0.f) { SetPlayerState(PState::MOVE_FL); }
            //R����������ڒn�W�J
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_GR);
            }
            break;

        case PState::MOVE_FL:   //���V�ړ�
            //�ړ����Ă��Ȃ��ꍇ�͐ڒn�ҋ@
            if (velocity.GetDistance() == 0.f) { SetPlayerState(PState::IDLE_FL); }
            //�ڒn������ڒn���s
            if (player_.IsGround()) { SetPlayerState(PState::WALK_GR); }
            //R���������畂�V�W�J
            if (input.GetState(PAD_INPUT::R1) == ON)
            {
                SetPlayerState(PState::DEPLOY_FL);
            }
            break;

        case PState::DEPLOY_GR: //�ڒn�W�J
            //R�𗣂�����ڒn�W�J����
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

        case PState::DEPLOY_FL: //���V�W�J
            //R�𗣂����畂�V�W�J����
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
    //��Ԃ̕ύX
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