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
        if (impl_)
        {
            return impl_->GetTaskOne(task_name);
        }
        return std::shared_ptr<T>();
    }
    //�w�肵���^�X�N���܂Ƃ߂ēn��
    template<class T>
    static std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskAll(const std::string& task_name)
    {
        if (impl_)
        {
            impl_->GetTaskAll(task_name);
        }
        return std::shared_ptr<std::vector<std::shared_ptr<T>>>();
    }

private:
    class Impl;
    static std::unique_ptr<Impl> impl_;
};