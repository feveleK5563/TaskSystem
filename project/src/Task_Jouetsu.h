#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Character.h"
#include "Task_BackCircle.h"

namespace Jouetsu
{
    const std::string   def_group ("�L�����N�^�[");   //�O���[�v��
    const std::string   def_task  ("�W���E�G�c����"); //�^�X�N��

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
        std::shared_ptr<Resource> res_; //�m�ۂ������\�[�X

        enum class JState
        {
            Nomal,
            Jorei,
            TrJorei,
            TrNomal,
        } state_;

        ImageDrawer jouetsu_image_; //�W���E�G�c����摜
        Character jouetsu_;         //���
        Math::Vec2 pivot_pos_;      //�����ʒu
        
        std::shared_ptr<BackCircle::Task> circle_;  //�~�`�̃u���b

    public:
        //�R���X�g���N�^
        Task();

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create();

        void Initialize();          //����������
        void Finalize() override;   //�I������
        void Update() override;     //�X�V
        void Draw() override;       //�`��

        const Math::Vec2& GetPivotPos();    //���S���W���擾
        Math::Box2D GetRect();              //�����蔻����擾

    private:
        void InputToStateTransition();
        Math::Vec2 Move();
    };
}