#include "Task_Camera.h"
#include "TaskDefData.h"
#include "SystemDefine.h"

namespace Camera
{
    //----------------------------------------------
    //�^�X�N�̃R���X�g���N�^
    Task::Task():
        TaskAbstract(def_task),
        speed_(12.f),
        camera_rect_(0, 0, SysDef::SizeX, SysDef::SizeY)
    {
        SetPriority(Priority::CAMERA);
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
        pos_ += velocity_ / speed_;
        /*if		(pos.x < 0.f) pos.x = 0.f;
        else if (pos.x > SysDef::SizeX) pos.x = SysDef::SizeX;
        if		(pos.y < 0.f) pos.y = 0.f;
        else if (pos.y > SysDef::SizeY) pos.y = SysDef::SizeY;*/
    }

    //----------------------------------------------
    //�ڕW�ƂȂ���W��ݒ�
    void Task::SetTargetPos(const Math::Vec2& target)
    {
        Math::Vec2 center(pos_);
        center.x += camera_rect_.x / 2.f;
        center.y += camera_rect_.y / 2.f;
        velocity_ = target - center;
    }

    //----------------------------------------------
    //���W���J���������ɂ��ĕԂ�
    Math::Vec2 Task::GetScreenPos(const Math::Vec2& target)
    {
        return target - pos_;
    }
}