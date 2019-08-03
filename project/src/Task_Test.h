#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Task_Physics.h"

namespace Test
{
    const std::string   task_name("Test");   // �^�X�N��
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
    
        Resource();     // �R���X�g���N�^
        ~Resource();    // �f�X�g���N�^
        static std::shared_ptr<Resource> Create();  // ���\�[�X�̐���
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  // �m�ۂ������\�[�X
        ImageDrawer drawer;
        Physics::TaskPtr physics;

    public:
        //�R���X�g���N�^
        Task();

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create();

        void Initialize() override; // ����������
        void Finalize() override;   // �I������
        void Update() override;     // �X�V
        void Draw() override;       // �`��
    };
    using TaskPtr = std::shared_ptr<Task>;
}