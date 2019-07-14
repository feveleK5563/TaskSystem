#include "TaskAbstract.h"
#include "Utility.h"

TaskAbstract::TaskAbstract(const std::string& task_name):
    task_name_(task_name),
    priority_(0.f),
    task_state_(TaskState::Active)
{
    DOUT << "yCreate TaskzTask:" << task_name_ << std::endl;
}

TaskAbstract::~TaskAbstract()
{
    DOUT << "yDelete TaskzTask:" << task_name_ << std::endl;
}

//•`‰æ—Dæ“x‚ðÝ’è
void TaskAbstract::SetPriority(float set_priority)
{
    priority_ = set_priority;
}
//ƒ^ƒXƒN‚Ìó‘Ô‚ðÝ’è
void TaskAbstract::SetTaskState(TaskState set_task_state)
{
    task_state_ = set_task_state;
}


//ƒ^ƒXƒN–¼‚ðŽæ“¾
const std::string& TaskAbstract::GetTaskName()
{
    return task_name_;
}
//•`‰æ—Dæ“x‚ðŽæ“¾
const float& TaskAbstract::GetPriority()
{
    return priority_;
}
//ƒ^ƒXƒN‚Ìó‘Ô‚ðŽæ“¾
const TaskState& TaskAbstract::GetTaskState()
{
    return task_state_;
}