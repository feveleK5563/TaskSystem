#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Character.h"
#include "ImageDrawer.h"
#include "Task_EnemyKata.h"

namespace TestEnemy
{
    const std::string   def_task  ("�G�e�X�g");      //�^�X�N��

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;

    public:
        std::string image_name_;

        Resource();     //�R���X�g���N�^
        ~Resource();    //�f�X�g���N�^
        static std::shared_ptr<Resource> Create();  //���\�[�X�̐���
    };

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_;	//�m�ۂ������\�[�X

        ImageDrawer enemy_image_;
        Character enemy_;

        std::shared_ptr<EnemyKata::Task> kata;

    public:
        //�R���X�g���N�^
        Task(const Math::Vec2& pos);
        
        //�f�X�g���N�^
        ~Task();
        
        //�^�X�N�̐���
        static std::shared_ptr<Task> Create(const Math::Vec2& pos);

        void Initialize();          //����������
        void Finalize() override;   //�I������
        void Update() override;     //�X�V
        void Draw() override;       //�`��
    };
}