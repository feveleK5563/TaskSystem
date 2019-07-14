#include <algorithm>
#include "TaskSystem.h"
#include "Utility.h"

// タスクシステムの実装部分
class TaskSystem::Impl
{
private:
    std::vector<std::shared_ptr<TaskAbstract>> task_;
    std::vector<std::shared_ptr<TaskAbstract>> add_task_;
    std::unordered_map<std::string,
        std::vector<std::shared_ptr<TaskAbstract>>> task_data_;

    bool sort_flag_;

public:
    Impl() : sort_flag_(false) {}

    ~Impl()
    {
        AllDeleteTask();
    }

    // 更新
    void Update()
    {
        if (GetAllTaskNum() > 0)
        {
            AllUpdate();        // 全てのタスクのUpdateを呼ぶ
            AddTask();          // 追加予定のタスクを追加する
            StateDeleteTask();  // 状態がDeleteのタスクを削除する
            SortTask();         // priorityを基に昇順にソートする
        }
    }
    // 描画
    void Draw()
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
    void AddTask(std::shared_ptr<TaskAbstract> create_task)
    {
        if (create_task != nullptr)
        {
            add_task_.emplace_back(create_task);
            task_data_[add_task_.back()->GetTaskName()].emplace_back(create_task);
            create_task->Initialize();
        }
    }

    // 指定したタスクが存在しているか調べる
    bool IsHaveTask(const std::string& task_name)
    {
        return task_data_.find(task_name) != task_data_.end();
    }
    // 指定したタスクの状態を変更する
    void SetStateTask(const std::string& task_name, TaskState task_state)
    {
        if (!IsHaveTask(task_name))
            return;

        for (auto it : task_data_[task_name])
        {
            it->SetTaskState(task_state);
        }
    }
    // 指定したタスクを削除する
    void KillTask(const std::string& task_name)
    {
        SetStateTask(task_name, TaskState::Kill);
    }

    // 登録されているタスクの状態を全てKillにする
    void AllSetStateTask(TaskState task_state)
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
    void AllDeleteTask()
    {
        task_.clear();
        task_.emplace_back();

        add_task_.clear();
        add_task_.emplace_back();

        task_data_.clear();
    }

    // 全タスク数を取得する
    int GetAllTaskNum()
    {
        size_t num = add_task_.size() + task_.size();
        return (int)num;
    }

    // 指定したタスクの内、先頭のみを渡す
    template<class T>
    std::shared_ptr<T> GetTaskOne(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            return std::static_pointer_cast<T>(task_data_[task_name].front());
        }
        return std::shared_ptr<T>();
    }
    //指定したタスクをまとめて渡す
    template<class T>
    std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        std::shared_ptr<std::vector<std::shared_ptr<T>>> gt;

        if (IsHaveTask(task_name))
        {
            gt = std::make_shared<std::vector<std::shared_ptr<T>>>();

            gt->reserve(task_data_[task_name].size());

            for (auto it : task_data_[task_name])
            {
                gt->emplace_back(std::static_pointer_cast<T>(it));
            }
        }
        return gt;
    }

private:
    // 全てのタスクのUpdateを呼ぶ
    void AllUpdate()
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
    void AddTask()
    {
        if (add_task_.empty()) { return; }

        task_.insert(task_.end(), add_task_.begin(), add_task_.end());
        add_task_.clear();
        add_task_.shrink_to_fit();
        sort_flag_ = true;
    }
    // 状態がDeleteのタスクを削除する
    void StateDeleteTask()
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
    void SortTask()
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
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// インスタンスを生成する
void TaskSystem::Create()
{
    if (impl_)
    {
        impl_ = std::make_unique<Impl>();
    }
}

// インスタンスを解放する
void TaskSystem::Delete()
{
    impl_.reset();
}

void TaskSystem::Update()
{
    if (impl_)
    {
        impl_->Update();
    }
}

void TaskSystem::Draw()
{
    if (impl_)
    {
        impl_->Draw();
    }
}

void TaskSystem::AddTask(std::shared_ptr<TaskAbstract> create_task)
{
    if (impl_)
    {
        impl_->AddTask(create_task);
    }
}

bool TaskSystem::IsHaveTask(const std::string& task_name)
{
    if (impl_)
    {
        return impl_->IsHaveTask(task_name);
    }
    return false;
}

void TaskSystem::SetStateTask(const std::string& task_name, TaskState task_state)
{
    if (impl_)
    {
        impl_->SetStateTask(task_name, task_state);
    }
}

void TaskSystem::KillTask(const std::string& task_name)
{
    if (impl_)
    {
        impl_->KillTask(task_name);
    }
}

void TaskSystem::AllSetStateTask(TaskState task_state)
{
    if (impl_)
    {
        impl_->AllSetStateTask(task_state);
    }
}

void TaskSystem::AllDeleteTask()
{
    if (impl_)
    {
        impl_->AllDeleteTask();
    }
}

int TaskSystem::GetAllTaskNum()
{
    if (impl_)
    {
        return impl_->GetAllTaskNum();
    }
    return 0;
}