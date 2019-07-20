#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Utility.h"

enum struct TaskState
{
    Active,     //�ʏ�
    Sleep,      //�X�V��~
    DeepSleep,  //�X�V�ƕ`���~
    Kill,       //���ŗv��
    Delete,     //����(���i�͎g��Ȃ�����)
}; 

class TaskAbstract
{
private:
    const std::string   task_name_;     //�^�X�N��
    float               priority_;      //�`��D��x
    TaskState           task_state_;    //���

public:

    //�R���X�g���N�^
    TaskAbstract(const std::string& task_name);

    //�f�X�g���N�^
    virtual ~TaskAbstract();

    virtual void Initialize() = 0;  //����������(�K�{)
    virtual void Finalize() = 0;    //�I������(�K�{)
    virtual void Update() {};       //�X�V
    virtual void Draw() {};         //�`��

    void SetPriority(float set_priority);        //�`��D��x��ݒ�
    void SetTaskState(TaskState set_task_state); //�^�X�N�̏�Ԃ�ݒ�

    const std::string&  GetTaskName();  //�^�X�N�����擾
    const float&        GetPriority();  //�`��D��x���擾
    const TaskState&    GetTaskState(); //�^�X�N�̏�Ԃ��擾
};