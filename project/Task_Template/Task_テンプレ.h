#pragma once
#include "DxLib.h"
#include "TaskSystem.h"

namespace �^�X�N��
{
    const std::string   def_group (�O���[�v��); //�O���[�v��
    const std::string   def_task  (�^�X�N��);   //�^�X�N��
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
    
        Resource();     //�R���X�g���N�^
        ~Resource();    //�f�X�g���N�^
        static std::shared_ptr<Resource> Create();  //���\�[�X�̐���
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  //�m�ۂ������\�[�X

    public:
        //�R���X�g���N�^
        Task();

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create();

        void Initialize() override; //����������
        void Finalize() override;   //�I������
        void Update() override;     //�X�V
        void Draw() override;       //�`��
    };
}