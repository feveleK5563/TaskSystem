#include "Task_TestEnemy.h"
#include "TaskDefData.h"
#include "ImageLoader.h"
#include "Utility.h"
#include "Task_Mudra.h"

namespace TestEnemy
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    //���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        image_name_ = "TestEnemy";

        ImageLoader::LoadOneImage(image_name_, "data/image/testEnemy.png");
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
    Task::Task(const Math::Vec2& pos):
        TaskAbstract(def_task),
        res_(Resource::Create()),
        kata(EnemyKata::Task::Create(40.f, 3, 1, 6))
    {
        SetPriority(Priority::ENEMY);
        enemy_.SetPos(pos);
    }
    //----------------------------------------------
    //�^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    //�^�X�N�̐���
    std::shared_ptr<Task> Task::Create(const Math::Vec2& pos)
    {
        std::shared_ptr<Task> task = 
            std::make_shared<Task>(pos);
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
        enemy_image_.Initialize(res_->image_name_, Math::BoxCP::BOTTOM_MIDDLE);
        enemy_image_.SetScale(Ratio::layer_main);
        enemy_image_.SetTurnFlag(false);

        enemy_.SetBoxCP(Math::BoxCP::BOTTOM_MIDDLE);
        enemy_.SetLandRect(Math::Box2D(0, 0, 96, 96));
        enemy_.SetIsGravity(true);
    }

    //----------------------------------------------
    //�I������
    //----------------------------------------------
    void Task::Finalize()
    {
        (void)Create(Math::Vec2(enemy_.GetCenterPos().x, 200.f));
        kata->SetTaskState(TaskState::Kill);
    }

    //----------------------------------------------
    //�X�V
    //----------------------------------------------
    void Task::Update()
    {
        enemy_.NoSinkMove(Math::Vec2(-1, 0));
        kata->SetDrawPos(enemy_.GetPosForCam(true));

        if (kata->GetHitState() == MLine::MHit::Parfect)
        {
            SetTaskState(TaskState::Kill);
        }
    }

    //----------------------------------------------
    //�`��
    //----------------------------------------------
    void Task::Draw()
    {
        auto mudra = TaskSystem::GetTaskOne<Mudra::Task>(Mudra::def_task);
        if (mudra && mudra->IsActive())
        {
            enemy_image_.DrawSilhouette(enemy_.GetPosForCam(), Color(144, 96, 230));
        }
        else
        {
            enemy_image_.Draw(enemy_.GetPosForCam());
        }
        //enemy.DrawRect(false);
    }
}