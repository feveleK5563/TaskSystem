#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "Math.h"
#include "ImageDrawer.h"
#include "Counter.hpp"

namespace BackCircle
{
    const std::string   def_task  ("����t�B�[���h�̉~�`");   //�^�X�N��

    //----------------------------------------------
    //�V�F�[�_�[�ɑ�����
    struct CircleInfo
    {
        FLOAT2 window_size; //��ʃT�C�Y
        FLOAT2 center_pos;  //���S���W
        float radius;       //���a
        bool color_flag;    //���F�t���O
        float   r;
        float   g;
        float   b;
        float   a;

        CircleInfo():
            window_size({0.f, 0.f}),
            center_pos({0.f, 0.f}),
            radius(0.f),
            color_flag(false),
            r(0.f), g(0.f), b(0.f), a(0.f) {}
    };

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;
    
    public:
        std::string shader_name;
        std::string buffer_name;
    
        Resource();     //�R���X�g���N�^
        ~Resource();    //�f�X�g���N�^
        static std::shared_ptr<Resource> Create();  //���\�[�X�̐���
    };
    
    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        const float SPREAD_SPEED_ = 90.f;

        std::shared_ptr<Resource> res_;  //�m�ۂ������\�[�X

        CircleInfo info_;
        Counter<float> counter_;    //���a�T�C�Y�̕ω�

    public:
        //�R���X�g���N�^
        Task(const Color& color);

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create(const Color& color);

        void Initialize() override; //����������
        void Finalize() override;   //�I������
        void Update() override;     //�X�V
        void Draw() override;       //�`��

        //���F�t���O�ݒ�
        void SetColorFlag(bool color_flag);

        //���W�ݒ�
        void SetPos(const Math::Vec2& pos);
    };
}