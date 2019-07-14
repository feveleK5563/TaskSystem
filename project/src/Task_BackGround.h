#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace BackGround
{
    const std::string   def_task  ("�w�i1");       //�^�X�N��
    
    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
        std::string back_image_;
    
        Resource();     //�R���X�g���N�^
        ~Resource();    //�f�X�g���N�^
        static std::shared_ptr<Resource> Create();  //���\�[�X�̐���
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;  //�m�ۂ������\�[�X
        ImageDrawer back_;

    public:
        //�R���X�g���N�^
        Task();

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create();

        void Initialize() override; //����������
        void Finalize() override;   //�I������
        void Draw() override;       //�`��
    };
}