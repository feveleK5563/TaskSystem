#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "Character.h"

namespace Player
{
    enum struct PState
    {
        IDLE_GR = 0,  //�ҋ@_�ڒn
        IDLE_FL,      //�ҋ@_�؋�
        WALK_GR,      //���s_�ڒn
        MOVE_FL,      //�ړ�_�؋�
        DEPLOY_GR,    //�W�J_�ڒn
        DEPLOY_FL,    //�W�J_�؋�
    };

    const std::string   def_task  ("�v���C���[");   //�^�X�N��
    
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
        std::shared_ptr<Resource> res_;  //�m�ۂ������\�[�X

        ImageDrawer player_image_;  //�v���C���[�摜
        Character player_;          //�v���C���[�L�����N�^�[���
        PState state_;              //�v���C���[�̏��

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

        Math::Vec2 GetCenterPos();  //���W�擾
        bool GetIsTurn();           //�摜�����]����Ă��邩�ۂ����擾(���]����Ă�����true)

    private:
        //��Ԃɉ����������ƈړ������̎擾
        Math::Vec2 InputToGetMovingDirection();
        //��ԑJ��
        void StateTransition(const Math::Vec2& velocity);

        //��Ԃ̕ύX
        void SetPlayerState(PState state, bool is_reset_time = true);
    };
}