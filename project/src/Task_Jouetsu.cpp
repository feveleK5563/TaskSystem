#include "Task_Jouetsu.h"
#include "TaskDefData.h"
#include "ImageLoader.h"
#include "PadInputConfig.h"
#include "Task_Player.h"
#include "Task_Mudra.h"
#include "PadInputConfig.h"

namespace Jouetsu
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        image_name_ = "Jouetsu";

        auto& imgl = ImageLoader::GetInstance();
        imgl.LoadDivImage(image_name_, "data/image/jouetsu.png", 12, 6, 2, 32, 32);

        imgl.AddAnimationData(image_name_, 0, 5, 8.f, true);        //�ʏ펞
        imgl.AddAnimationData(image_name_, 6, 11, 2.5f, false);     //���샂�[�h�J��
        imgl.AddAnimationData(image_name_, 11, 11, 8.f, true);      //���샂�[�h��
        imgl.AddAnimationData(image_name_, 11, 6, 2.5f, false);     //�ʏ�J��
    }
    //----------------------------------------------
    //���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ImageLoader::GetInstance().DeleteImageData(image_name_);
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
        state_(JState::Nomal)
    {
        SetPriority(Priority::JOUETSU);
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
        TaskSystem::Get().AddTask(task);

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
        jouetsu_image_.Initialize(res_->image_name_, Math::BoxCP::CENTER);
        jouetsu_image_.SetScale(Ratio::layer_main);
        jouetsu_image_.SetTurnFlag(false);
        jouetsu_image_.ChangeAnimPattern(0, true);

        jouetsu_.SetBoxCP(Math::BoxCP::CENTER);
        jouetsu_.SetIsGravity(false);
        jouetsu_.SetPos(Math::Vec2(100, 100));
        jouetsu_.SetLandRect(Math::Box2D(0, 0, 10, 10));
        jouetsu_.SetVelocity(1.f);

        circle_ = BackCircle::Task::Create(Color(1.f, 1.f, 1.f, 0.8f));
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
        jouetsu_image_.AnimUpdate();

        InputToStateTransition();
        
        jouetsu_.NomalMove(Move());

        circle_->SetPos(jouetsu_.GetPosForCam());
    }

    //----------------------------------------------
    //�`��
    //----------------------------------------------
    void Task::Draw()
    {
        jouetsu_image_.Draw(jouetsu_.GetPosForCam());
        //jouetsu.DrawRect(false);
    }

    //----------------------------------------------
    //���S���W���擾
    const Math::Vec2& Task::GetPivotPos()
    {
        return pivot_pos_;
    }

    //----------------------------------------------
    //�����蔻����擾
    Math::Box2D Task::GetRect()
    {
        return jouetsu_.GetLandRect();
    }

    //----------------------------------------------
    void Task::InputToStateTransition()
    {
        auto& input = PadInputConfig::GetInstance(0);
        switch (state_)
        {
        case JState::Nomal: //�ʏ탂�[�h
            if (input.GetState(PAD_INPUT::R1) != OFF)
            {
                jouetsu_image_.ChangeAnimPattern(1, true);
                state_ = JState::TrJorei;
            }
            break;

        case JState::TrJorei: //���샂�[�h�J��
            if (input.GetState(PAD_INPUT::R1) != ON)
            {
                jouetsu_image_.ChangeAnimPattern(3, true);
                state_ = JState::TrNomal;
                break;
            }
            if (jouetsu_image_.IsAnimEnd())
            {
                circle_->SetColorFlag(true);
                jouetsu_image_.ChangeAnimPattern(2, true);
                state_ = JState::Jorei;
                (void)Mudra::Task::Create();
            }
            break;

        case JState::Jorei: //���샂�[�h
            if (input.GetState(PAD_INPUT::R1) != ON)
            {
                circle_->SetColorFlag(false);
                jouetsu_image_.ChangeAnimPattern(3, true);
                state_ = JState::TrNomal;
            }
            break;

        case JState::TrNomal: //�ʏ탂�[�h�J��
            if (jouetsu_image_.IsAnimEnd())
            {
                jouetsu_image_.ChangeAnimPattern(0, true);
                state_ = JState::Nomal;
            }
            break;
        }
    }

    //----------------------------------------------
    Math::Vec2 Task::Move()
    {
        Math::Vec2 velocity;
        auto player = TaskSystem::Get().GetTaskOne<Player::Task>(Player::def_task);
        Math::Vec2 ppos = player->GetCenterPos();
        pivot_pos_ = pivot_pos_ + ((ppos - pivot_pos_) / 3.f);

        if (state_ == JState::Jorei || state_ == JState::TrJorei)
        {
            velocity = (ppos - jouetsu_.GetPos()) / 3.f;

            //�E�X�e�B�b�N�ł̑���
            auto& input = PadInputConfig::GetInstance(0);
            Math::Vec2 rstick = input.GetVecStickR();
            if (rstick.GetDistance() > 0.f)
            {
                velocity += (rstick * 60.f);
            }
        }
        else
        {
            ppos.y -= 40.f;
            if (player->GetIsTurn())
            {
                ppos.x += 50.f;
            }
            else
            {
                ppos.x -= 50.f;
            }

            velocity = ppos - jouetsu_.GetPos();
            velocity /= 20.f;
        }

        return velocity;
    }
}