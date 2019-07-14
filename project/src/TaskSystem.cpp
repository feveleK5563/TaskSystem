#include <algorithm>
#include "TaskSystem.h"
#include "Utility.h"

TaskSystem::TaskSystem(): sort_flag_(false) {}

TaskSystem::~TaskSystem()
{
    AllDeleteTask();
}

// 更新
void TaskSystem::Update()
{
    if (GetAllTaskNum() > 0)
    {
        AllUpdate();        // 全てのタスクのUpdateを呼ぶ
        AddTask();          // 追加予定のタスクを追加する
        StateDeleteTask();  // 状態がDeleteのタスクを削除する
        SortTask();         // priorityを基に昇順にソートするv
    }
}

// 描画
void TaskSystem::Draw()
{
    for (auto& it : task_)
    {
        if (it->GetTaskState() != TaskState::Kill ||
            it->GetTaskState() != TaskState::DeepSleep)
        {
            it->Draw();
        }
    }
}

// タスクを追加する
void TaskSystem::AddTask(std::shared_ptr<TaskAbstract> create_task)
{
    if (create_task != nullptr)
    {
        add_task_.emplace_back(create_task);
        task_data_[add_task_.back()->GetTaskName()].emplace_back(create_task);
        create_task->Initialize();
    }
}

TaskSystem* TaskSystem::ts_ = nullptr;

// 指定したタスクが存在しているか調べる
bool TaskSystem::IsHaveTask(const std::string& task_name)
{
    return task_data_.find(task_name) != task_data_.end();
}

// 指定したタスクの状態を変更する
void TaskSystem::SetStateTask(const std::string& task_name, TaskState task_state)
{
    if (!IsHaveTask(task_name))
        return;

    for (auto it : task_data_[task_name])
    {
        it->SetTaskState(task_state);
    }
}

// 指定したタスクを削除する
void TaskSystem::KillTask(const std::string& task_name)
{
    SetStateTask(task_name, TaskState::Kill);
}

// 登録されているタスクの状態を全てKillにする
void TaskSystem::AllSetStateTask(TaskState task_state)
{
    for (auto map : task_data_)
    {
        for (auto it : map.second)
        {
            it->SetTaskState(task_state);
        }
    }
}

// 登録済、登録予定のタスクを全て強制削除する(デストラクタで呼ばれる)
void TaskSystem::AllDeleteTask()
{
    task_.clear();
    task_.emplace_back();

    add_task_.clear();
    add_task_.emplace_back();

    task_data_.clear();
}

// 全タスク数を取得する
int TaskSystem::GetAllTaskNum()
{
    size_t num = add_task_.size() + task_.size();
    return (int)num;
}

// インスタンスを得る
TaskSystem& TaskSystem::Get()
{
    assert(ts_ != nullptr && "TaskSystem hasn't been created!");
    return *ts_;
}

// インスタンスを生成する
void TaskSystem::Create()
{
    if (ts_ == nullptr)
    {
        ts_ = new TaskSystem();
    }
}

// インスタンスを解放する
void TaskSystem::Delete()
{
    Util::SafeDelete(ts_);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// 全てのタスクのUpdateを呼ぶ
void TaskSystem::AllUpdate()
{
    // 先に登録予定タスクのUpdateを呼ぶ
    for (auto& it : add_task_)
    {
        if (it->GetTaskState() == TaskState::Active)
        {
            it->Update();
        }
    }

    // 登録済みタスクのUpdateを呼ぶ
    for (auto& it : task_)
    {
        switch (it->GetTaskState())
        {
        case TaskState::Active:	// 状態が通常の場合は普通に更新
            it->Update();
            break;

        case TaskState::Kill:	// 状態が削除要請中の場合は終了処理を呼ぶ
            it->Finalize();
            it->SetTaskState(TaskState::Delete);
            break;
        }
    }
}

// 追加予定のタスクを追加する
void TaskSystem::AddTask()
{
    if (add_task_.empty()) { return; }

    task_.insert(task_.end(), add_task_.begin(), add_task_.end());
    add_task_.clear();
    add_task_.shrink_to_fit();
    sort_flag_ = true;
}

// 状態がDeleteのタスクを削除する
void TaskSystem::StateDeleteTask()
{
    // 削除する条件式(状態がDeleteの時に削除)
    auto deleteCondition =
        [](std::shared_ptr<TaskAbstract>& obj)
    {
        return (obj->GetTaskState() == TaskState::Delete);
    };

    // オブジェクトの削除
    {
        const auto& removeIt = std::remove_if(task_.begin(), task_.end(), deleteCondition);
        task_.erase(removeIt, task_.end());
        task_.shrink_to_fit();
    }

    // データの削除
    for (auto it = task_data_.begin(); it != task_data_.end();)
    {
        const auto& remove_it = std::remove_if(it->second.begin(), it->second.end(), deleteCondition);
        it->second.erase(remove_it, it->second.end());
        it->second.shrink_to_fit();

        if (it->second.empty())
        {
            sort_flag_ = true;
            it = task_data_.erase(it);
            continue;
        }
        ++it;
    }
}

// priorityを基に昇順にソートする
void TaskSystem::SortTask()
{
    if (sort_flag_)
    {
        sort_flag_ = false;
        std::sort(task_.begin(), task_.end(),
            [](std::shared_ptr<TaskAbstract>& left, std::shared_ptr<TaskAbstract>& right)
        {
            return (left->GetPriority() < right->GetPriority());
        }
        );
    }
}