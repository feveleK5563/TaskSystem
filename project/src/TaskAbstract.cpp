#include "TaskAbstract.h"
#include "Utility.h"

TaskAbstract::TaskAbstract(const std::string& task_name):
    task_name_(task_name),
    priority_(0.f),
    task_state_(TaskState::Active)
{
    DOUT << "�yCreate Task�zTask:" << task_name_ << std::endl;
}

TaskAbstract::~TaskAbstract()
{
    DOUT << "�yDelete Task�zTask:" << task_name_ << std::endl;
}

//�`��D��x��ݒ�
void TaskAbstract::SetPriority(float set_priority)
{
    priority_ = set_priority;
}
//�^�X�N�̏�Ԃ�ݒ�
void TaskAbstract::SetTaskState(TaskState set_task_state)
{
    task_state_ = set_task_state;
}


//�^�X�N�����擾
const std::string& TaskAbstract::GetTaskName()
{
    return task_name_;
}
//�`��D��x���擾
const float& TaskAbstract::GetPriority()
{
    return priority_;
}
//�^�X�N�̏�Ԃ��擾
const TaskState& TaskAbstract::GetTaskState()
{
    return task_state_;
}