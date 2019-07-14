#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
private:
    std::vector<std::shared_ptr<TaskAbstract>> task_;
    std::vector<std::shared_ptr<TaskAbstract>> add_task_;
    std::unordered_map<std::string,
            std::vector<std::shared_ptr<TaskAbstract>>> task_data_;

    bool sort_flag_;

    TaskSystem();
    static TaskSystem* ts_;

public:
    ~TaskSystem();

    void Update();                                           // �X�V
    void Draw();                                             // �`��
    void AddTask(std::shared_ptr<TaskAbstract> create_task); // �^�X�N��ǉ�����

    // �w�肵���^�X�N�����݂��Ă��邩���ׂ�
    bool IsHaveTask(const std::string& task_name);
    // �w�肵���^�X�N�̏�Ԃ�ύX����
    void SetStateTask(const std::string& task_name, TaskState task_state);
    // �w�肵���^�X�N���폜����
    void KillTask(const std::string& task_name);

    // �o�^����Ă���^�X�N�̏�Ԃ�S�ĕύX����
    void AllSetStateTask(TaskState task_state);
    // �o�^����Ă���^�X�N��S�ċ����폜����(�f�X�g���N�^�ŌĂ΂��)
    void AllDeleteTask();

    // �S�^�X�N�����擾����
    int GetAllTaskNum();

    // �w�肵���^�X�N�̓��A�擪�݂̂�n��
    template<class T>
    std::shared_ptr<T> GetTaskOne(const std::string& task_name)
    {
        if (IsHaveTask(task_name))
        {
            return std::static_pointer_cast<T>(task_data_[task_name].front());
        }
        return std::shared_ptr<T>();
    }
    //�w�肵���^�X�N���܂Ƃ߂ēn��
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

    //�C���X�^���X�𓾂�
    static TaskSystem& Get();
    //�C���X�^���X�𐶐�����
    static void Create();
    //�C���X�^���X���������
    static void Delete();

private:
    void AllUpdate();       //�S�Ẵ^�X�N��Update���Ă�
    void AddTask();         //�ǉ��\��̃^�X�N��ǉ�����
    void StateDeleteTask(); //��Ԃ�Delete�̃^�X�N���폜����
    void SortTask();        //priority����ɏ����Ƀ\�[�g����
};