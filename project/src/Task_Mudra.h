#pragma once
#include <array>
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "MLine.h"

namespace Mudra
{
    const std::string   def_task  ("�C��");        //�^�X�N��

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
        float ratio_;   //�g�嗦

        bool is_active_;
        bool release_;
        Math::Vec2 pos_;
        ImageDrawer mudra_image_;

        std::array<Math::Box2D, 4> mudra_rect_;
        int before_box_num_;
        int now_box_num_;

        MLine mline_;

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

        //�`�悳�ꂽ�����擾
        int GetMLine();
        //�����Ԃ��擾
        bool IsActive();

    private:
        //���W�̐ݒ�
        void SetPos(const Math::Vec2& pos);
        //��ڐG�ʒu�Ƃ̐ڐG����
        void HitMudraPoint(const Math::Box2D& rect);
    };
}