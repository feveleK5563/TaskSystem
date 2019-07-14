#pragma once
#include "DxLib.h"
#include "TaskSystem.h"
#include "MLine.h"

namespace EnemyKata
{
    const std::string   def_task  ("EnemyKata");   //�^�X�N��

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        Math::Vec2 pos_;
        MLine mline_;

    public:
        //�R���X�g���N�^
        Task(float dist, int thick, int max_line, int min_line);

        //�f�X�g���N�^
        ~Task();

        //�^�X�N�̐���
        static std::shared_ptr<Task> Create(float dist, int thick, int max_line, int min_line);

        void Initialize() override; //����������
        void Finalize() override;   //�I������
        void Draw() override;       //�`��

        void SetDrawPos(const Math::Vec2& pos);
        MLine::MHit GetHitState();  //Mudra�Ƃ̔��茋�ʂ��擾����
    };
}