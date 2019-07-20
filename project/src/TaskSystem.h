#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
public:
    //�C���X�^���X�𐶐�����
    static void Create();
    //�C���X�^���X���������
    static void Delete();

    static void Update();                                           // �X�V
    static void Draw();                                             // �`��
    static void AddTask(std::shared_ptr<TaskAbstract> create_task); // �^�X�N��ǉ�����

    // �w�肵���^�X�N�����݂��Ă��邩���ׂ�
    static bool IsHaveTask(const std::string& task_name);
    // �w�肵���^�X�N�̏�Ԃ�ύX����
    static void SetStateTask(const std::string& task_name, TaskState task_state);
    // �w�肵���^�X�N���폜����
    static void KillTask(const std::string& task_name);

    // �o�^����Ă���^�X�N�̏�Ԃ�S�ĕύX����
    static void AllSetStateTask(TaskState task_state);
    // �o�^����Ă���^�X�N��S�ċ����폜����(�f�X�g���N�^�ŌĂ΂��)
    static void AllDeleteTask();

    // �S�^�X�N�����擾����
    static int GetAllTaskNum();

    // �w�肵���^�X�N�̓��A�擪�݂̂�n��
    template<class T>
    static std::shared_ptr<T> GetTaskOne(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            std::shared_ptr<TaskAbstract> task_data = GetTaskAbstractOne(task_name);
            return std::static_pointer_cast<T>(task_data);
        }
        return std::shared_ptr<T>();
    }
    // �w�肵���^�X�N���܂Ƃ߂ēn��
    template<class T>
    static std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            const std::vector<std::shared_ptr<TaskAbstract>>* task_data = GetTaskAbstractAll(task_name);
            if (!task_data)
            {
                return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
            }

            std::shared_ptr<std::vector<std::shared_ptr<T>>> gt =
                    std::make_shared<std::vector<std::shared_ptr<T>>>();

            gt->reserve(task_data->size());

            for (auto it : *task_data)
            {
                gt->emplace_back(std::static_pointer_cast<T>(it));
            }
            return gt;
        }
        return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
    }

private:
    static std::shared_ptr<TaskAbstract> GetTaskAbstractOne(const std::string& task_name);
    static const std::vector<std::shared_ptr<TaskAbstract>>* GetTaskAbstractAll(const std::string& task_name);

private:
    class Impl;
    static Impl* impl_;
};