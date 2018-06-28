#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(	const std::string& groupName,
							float priority,
							TaskState state):
	groupName(groupName),
	priority(priority),
	state(state) {}

//�������E��
void TaskAbstract::KillMe()
{
	state = TaskState::Kill;
}