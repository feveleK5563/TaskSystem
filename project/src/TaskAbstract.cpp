#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(	const std::string& groupName,
							const std::string& taskName,
							float priority,
							TaskState state):
	groupName(groupName),
	taskName(taskName),
	priority(priority),
	taskState(state) {}

//自分を殺す
void TaskAbstract::KillMe()
{
	taskState = TaskState::Kill;
}
//自分を停止状態にする
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

//描画優先度を設定
void TaskAbstract::SetPriority(float setPriority)
{
	priority = setPriority;
}
//タスクの状態を設定
void TaskAbstract::SetTaskState(TaskState setTaskState)
{
	taskState = setTaskState;
}


//タスクのグループ名を取得
const std::string& TaskAbstract::GetGroupName()
{
	return groupName;
}
//タスク名を取得
const std::string& TaskAbstract::GetTaskName()
{
	return taskName;
}
//描画優先度を取得
const float& TaskAbstract::GetPriority()
{
	return priority;
}
//タスクの状態を取得
const TaskState& TaskAbstract::GetTaskState()
{
	return taskState;
}