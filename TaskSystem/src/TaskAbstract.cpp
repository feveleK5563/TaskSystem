#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(	const std::string& groupName,
							const std::string& taskName,
							float priority,
							TaskState state):
	groupName(groupName),
	taskName(taskName),
	priority(priority),
	taskState(state) {}

//�������E��
void TaskAbstract::KillMe()
{
	taskState = TaskState::Kill;
}
//�������~��Ԃɂ���
void TaskAbstract::SleepMe()
{
	if (taskState == TaskState::Active)
	{
		taskState = TaskState::Sleep;
	}
	else if (taskState == TaskState::Sleep)
	{
		taskState = TaskState::Active;
	}
}

//�`��D��x��ݒ�
void TaskAbstract::SetPriority(float setPriority)
{
	priority = setPriority;
}
//�^�X�N�̏�Ԃ�ݒ�
void TaskAbstract::SetTaskState(TaskState setTaskState)
{
	taskState = setTaskState;
}


//�^�X�N�̃O���[�v�����擾
const std::string& TaskAbstract::GetGroupName()
{
	return groupName;
}
//�^�X�N�����擾
const std::string& TaskAbstract::GetTaskName()
{
	return taskName;
}
//�`��D��x���擾
const float& TaskAbstract::GetPriority()
{
	return priority;
}
//�^�X�N�̏�Ԃ��擾
const TaskState& TaskAbstract::GetTaskState()
{
	return taskState;
}