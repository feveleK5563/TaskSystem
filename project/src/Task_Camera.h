#pragma once
#include "DxLib.h"
#include "Math.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Camera
{
    const std::string   def_task  ("�J����"); //�^�X�N��

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        float speed_;
        Math::Vec2 pos_;
        Math::Vec2 velocity_;
        Math::Box2D camera_rect_;

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

        void SetTargetPos(const Math::Vec2& target);        //�ڕW�ƂȂ���W��ݒ�
        Math::Vec2 GetScreenPos(const Math::Vec2& target);  //���W���J���������ɂ��ĕԂ�
    };
}