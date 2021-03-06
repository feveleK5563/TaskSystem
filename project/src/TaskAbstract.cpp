#include "TaskAbstract.h"

TaskAbstract::TaskAbstract(const std::string& task_name,
                           float priority):
    task_name_(task_name),
    priority_(priority),
    task_state_(TaskState::Active)
{
    DOUT << "【Create Task】Task:" << task_name_ << std::endl;
}

TaskAbstract::~TaskAbstract()
{
    DOUT << "【Delete Task】Task:" << task_name_ << std::endl;
}

// 描画優先度を設定
void TaskAbstract::SetPriority(float set_priority)
{
    priority_ = set_priority;
}

// タスクの状態を設定
void TaskAbstract::SetTaskState(TaskState set_task_state)
{
    task_state_ = set_task_state;
}

// 削除
void TaskAbstract::Kill()
{
    task_state_ = TaskState::Kill;
}

// タスク名を取得
const std::string& TaskAbstract::GetTaskName()
{
    return task_name_;
}

// 描画優先度を取得
const float& TaskAbstract::GetPriority()
{
    return priority_;
}

// タスクの状態を取得
const TaskState& TaskAbstract::GetTaskState()
{
    return task_state_;
}