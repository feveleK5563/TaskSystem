#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Math.h"

namespace Physics
{
    const std::string   task_name("Physics");   // �^�X�N��
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        Math::Vec2 position_;       // ���W
        Math::Vec2 velocity_;       // ���x
        Math::Vec2 acceleration_;   // �����x
        float angle_;               // �p�x
        float angle_velocity_;      // �p���x
        float angle_acceleration_;  // �p�����x

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

        void SetPos(const Math::Vec2& position);        // ���W�ݒ�
        void SetVel(const Math::Vec2& velocity);        // ���x�ݒ�
        void SetAcc(const Math::Vec2& acceleration);    // �����x�ݒ�
        void SetAng(float angle);                       // �p�x
        void SetAngVel(float angle_velocity);           // �p���x
        void SetAngAcc(float angle_acceleration);       // �p�����x

        const Math::Vec2& GetPos(); // ���W�擾
        const float& GetAng();      // �p�x�擾
    };
    using TaskPtr = std::shared_ptr<Task>;
}