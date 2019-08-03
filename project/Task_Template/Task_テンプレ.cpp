#include "Task_�^�X�N��.h"

namespace �^�X�N��
{
    std::weak_ptr<Resource> Resource::instance_;
    //----------------------------------------------
    // ���\�[�X�̃R���X�g���N�^
    Resource::Resource()
    {
    }
    //----------------------------------------------
    // ���\�[�X�̃f�X�g���N�^
    Resource::~Resource()
    {
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
    Task::Task():
        TaskAbstract(task_name, 0.f),
        res_(Resource::Create())
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
    }

    //----------------------------------------------
    // �I������
    //----------------------------------------------
    void Task::Finalize()
    {
    }

    //----------------------------------------------
    // �X�V
    //----------------------------------------------
    void Task::Update()
    {
    }

    //----------------------------------------------
    // �`��
    //----------------------------------------------
    void Task::Draw()
    {
    }
}