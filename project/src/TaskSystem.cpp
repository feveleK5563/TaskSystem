#include <algorithm>
#include "TaskSystem.h"
#include "Utility.h"

// �^�X�N�V�X�e���̎�������
class TaskSystem::Impl
{
private:
    static const int TASK_BUFFER_SIZE = 1024;

    std::vector<std::shared_ptr<TaskAbstract>> task_;
    std::vector<std::shared_ptr<TaskAbstract>> add_task_;
    std::unordered_map<std::string,
        std::vector<std::shared_ptr<TaskAbstract>>> task_data_;

    bool sort_flag_;

public:
    Impl() : sort_flag_(false)
    {
        task_.reserve(TASK_BUFFER_SIZE);
        add_task_.reserve(TASK_BUFFER_SIZE);
    }

    ~Impl()
    {
        AllDeleteTask();
    }

    // �X�V
    void Update()
    {
        if (GetAllTaskNum() > 0)
        {
            AllUpdate();        // �S�Ẵ^�X�N��Update���Ă�
            AddTask();          // �ǉ��\��̃^�X�N��ǉ�����
            StateDeleteTask();  // ��Ԃ�Delete�̃^�X�N���폜����
            SortTask();         // priority����ɏ����Ƀ\�[�g����
        }
    }
    // �`��
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

    // �^�X�N��ǉ�����
    void AddTask(std::shared_ptr<TaskAbstract> create_task)
    {
        if (create_task != nullptr)
        {
            add_task_.emplace_back(create_task);
            task_data_[add_task_.back()->GetTaskName()].emplace_back(create_task);
            create_task->Initialize();
        }
    }

    // �w�肵���^�X�N�����݂��Ă��邩���ׂ�
    bool IsHaveTask(const std::string& task_name)
    {
        return task_data_.find(task_name) != task_data_.end();
    }
    // �w�肵���^�X�N�̏�Ԃ�ύX����
    void SetStateTask(const std::string& task_name, TaskState task_state)
    {
        if (!IsHaveTask(task_name))
            return;

        for (auto it : task_data_[task_name])
        {
            it->SetTaskState(task_state);
        }
    }
    // �w�肵���^�X�N���폜����
    void KillTask(const std::string& task_name)
    {
        SetStateTask(task_name, TaskState::Kill);
    }

    // �o�^����Ă���^�X�N�̏�Ԃ�S��Kill�ɂ���
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
    // �o�^�ρA�o�^�\��̃^�X�N��S�ċ����폜����(�f�X�g���N�^�ŌĂ΂��)
    void AllDeleteTask()
    {
        task_.clear();
        task_.emplace_back();

        add_task_.clear();
        add_task_.emplace_back();

        task_data_.clear();
    }

    // �S�^�X�N�����擾����
    int GetAllTaskNum()
    {
        size_t num = add_task_.size() + task_.size();
        return (int)num;
    }

    // �w�肵���^�X�N�̓��A�擪�݂̂�n��
    std::shared_ptr<TaskAbstract> GetTaskAbstractOne(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            return task_data_[task_name].front();
        }
        return std::shared_ptr<TaskAbstract>();
    }
    // �w�肵���^�X�N���܂Ƃ߂ēn��
    const std::vector<std::shared_ptr<TaskAbstract>>* GetTaskAbstractAll(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            return &task_data_[task_name];
        }
        return nullptr;
    }

private:
    // �S�Ẵ^�X�N��Update���Ă�
    void AllUpdate()
    {
        // ��ɓo�^�\��^�X�N��Update���Ă�
        for (auto& it : add_task_)
        {
            if (it->GetTaskState() == TaskState::Active)
            {
                it->Update();
            }
        }

        // �o�^�ς݃^�X�N��Update���Ă�
        for (auto& it : task_)
        {
            switch (it->GetTaskState())
            {
            case TaskState::Active:	// ��Ԃ��ʏ�̏ꍇ�͕��ʂɍX�V
                it->Update();
                break;

            case TaskState::Kill:	// ��Ԃ��폜�v�����̏ꍇ�͏I���������Ă�
                it->Finalize();
                it->SetTaskState(TaskState::Delete);
                break;
            }
        }
    }
    // �ǉ��\��̃^�X�N��ǉ�����
    void AddTask()
    {
        if (add_task_.empty()) { return; }

        task_.insert(task_.end(), add_task_.begin(), add_task_.end());
        add_task_.clear();
        add_task_.shrink_to_fit();
        sort_flag_ = true;
    }
    // ��Ԃ�Delete�̃^�X�N���폜����
    void StateDeleteTask()
    {
        // �폜���������(��Ԃ�Delete�̎��ɍ폜)
        auto deleteCondition =
            [](std::shared_ptr<TaskAbstract>& obj)
        {
            return (obj->GetTaskState() == TaskState::Delete);
        };

        // �I�u�W�F�N�g�̍폜
        {
            const auto& removeIt = std::remove_if(task_.begin(), task_.end(), deleteCondition);
            task_.erase(removeIt, task_.end());
            task_.shrink_to_fit();
        }

        // �f�[�^�̍폜
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
    // priority����ɏ����Ƀ\�[�g����
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
TaskSystem::Impl* TaskSystem::impl_ = nullptr;
TaskSystem::Impl* TaskSystem::GetImpl()
{
    assert(impl_ && "TaskSystem hasn't been created!!");
    return impl_;
}
//-----------------------------------------------------------------------------

// �C���X�^���X�𐶐�����
void TaskSystem::Create()
{
    if (!impl_)
    {
        impl_ = new Impl();
    }
}

// �C���X�^���X���������
void TaskSystem::Delete()
{
    Util::SafeDelete(impl_);
}

void TaskSystem::Update()
{
    GetImpl()->Update();
}

void TaskSystem::Draw()
{
    GetImpl()->Draw();
}

void TaskSystem::AddTask(std::shared_ptr<TaskAbstract> create_task)
{
    GetImpl()->AddTask(create_task);
}

bool TaskSystem::IsHaveTask(const std::string& task_name)
{
    return GetImpl()->IsHaveTask(task_name);
}

void TaskSystem::SetStateTask(const std::string& task_name, TaskState task_state)
{
    GetImpl()->SetStateTask(task_name, task_state);
}

void TaskSystem::KillTask(const std::string& task_name)
{
    GetImpl()->KillTask(task_name);
}

void TaskSystem::AllSetStateTask(TaskState task_state)
{
    GetImpl()->AllSetStateTask(task_state);
}

void TaskSystem::AllDeleteTask()
{
    GetImpl()->AllDeleteTask();
}

int TaskSystem::GetAllTaskNum()
{
    return GetImpl()->GetAllTaskNum();
}

std::shared_ptr<TaskAbstract> TaskSystem::GetTaskAbstractOne(const std::string& task_name)
{
    return GetImpl()->GetTaskAbstractOne(task_name);
}

const std::vector<std::shared_ptr<TaskAbstract>>* TaskSystem::GetTaskAbstractAll(const std::string& task_name)
{
    return GetImpl()->GetTaskAbstractAll(task_name);
}