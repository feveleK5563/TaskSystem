#include "Task_Physics.h"

namespace Physics
{
    //----------------------------------------------
    // �^�X�N�̃R���X�g���N�^
    Task::Task()
        : TaskAbstract(task_name, 0.f)
        , angle_(0.f)
        , angle_velocity_(0.f)
        , angle_acceleration_(0.f)
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
        position_ += velocity_;
        velocity_ += acceleration_;

        angle_ += angle_velocity_;
        angle_velocity_ += angle_acceleration_;
    }

    //��������������������������������������������������������������������������������������������
    //��������������������������������������������������������������������������������������������

    //----------------------------------------------
    // ���W�ݒ�
    void Task::SetPos(const Math::Vec2& position)
    {
        position_ = position;
    }
    //----------------------------------------------
    // ���x�ݒ�
    void Task::SetVel(const Math::Vec2& velocity)
    {
        velocity_ = velocity;
    }
    //----------------------------------------------
    // �����x�ݒ�
    void Task::SetAcc(const Math::Vec2& acceleration)
    {
        acceleration_ = acceleration;
    }
    //----------------------------------------------
    // �p�x�ݒ�
    void Task::SetAng(float angle)
    {
        angle_ = angle;
    }
    //----------------------------------------------
    // �p���x�ݒ�
    void Task::SetAngVel(float angle_velocity)
    {
        angle_velocity_ = angle_velocity;
    }
    //----------------------------------------------
    // �p�����x�ݒ�
    void Task::SetAngAcc(float angle_acceleration)
    {
        angle_acceleration_ = angle_acceleration;
    }

    //----------------------------------------------
    // ���W�擾
    const Math::Vec2& Task::GetPos()
    {
        return position_;
    }
    //----------------------------------------------
    // �p�x�ݒ�
    const float& Task::GetAng()
    {
        return angle_;
    }
}