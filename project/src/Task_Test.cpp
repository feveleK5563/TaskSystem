#include "Task_Test.h"
#include "ImageLoader.h"
#include "InputDXL.h"

namespace Test
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    // ���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
        ImageLoader::LoadOneImage("test", "data/image/test.png");
    }
    //----------------------------------------------
    // ���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
        ImageLoader::DeleteImageData("test");
    }
    //----------------------------------------------
    // ���\�[�X�̐���
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
    // �^�X�N�̃R���X�g���N�^
    Task::Task()
        : TaskAbstract(task_name, 0.f)
        , res_(Resource::Create())
    {
    }
    //----------------------------------------------
    // �^�X�N�̃f�X�g���N�^
    Task::~Task()
    {
    }
    //----------------------------------------------
    // �^�X�N�̐���
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
    // ����������
    //----------------------------------------------
    void Task::Initialize()
    {
        physics = Physics::Task::Create();
        physics->SetPos(Math::Vec2(640, 360));
        physics->SetVel(Math::Vec2(0, -10));
        physics->SetAcc(Math::Vec2(0.f, 0.25f));

        drawer.Initialize("test", Math::BoxCP::TOP_LEFT);
    }

    //----------------------------------------------
    // �I������
    //----------------------------------------------
    void Task::Finalize()
    {
        physics->Kill();
    }

    //----------------------------------------------
    // �X�V
    //----------------------------------------------
    void Task::Update()
    {
        auto input = InputDXL::GetKey();
        if (input[KEY_INPUT::SPACE] == DOWN)
        {
            physics->SetVel(Math::Vec2(0, -10));
        }
    }

    //----------------------------------------------
    // �`��
    //----------------------------------------------
    void Task::Draw()
    {
        drawer.Draw(physics->GetPos());
    }
}