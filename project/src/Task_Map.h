#pragma once
#include <vector>
#include <sstream>
#include "DxLib.h"
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Map
{
    //�u���b�N�̓���
    enum struct BlockTrait
    {
        Non     = -1,   //�����Ȃ�
        Nomal   = 0,    //���ʂ̕ǁA��
    };

    //��`�̃q�b�g�ʒu�����m�点���邽�߂̂��
    enum struct RectGirth
    {
        NON     = 0,        //����(�������Ă��Ȃ���������)
        U_LEFT  = 1 << 0,   //��̍���
        U_RIGHT = 1 << 1,   //��̉E��
        D_LEFT  = 1 << 2,   //���̍���
        D_RIGHT = 1 << 3,   //���̉E��
        L_UP    = 1 << 4,   //���̏㑤
        L_DOWN  = 1 << 5,   //���̉���
        R_UP    = 1 << 6,   //���̏㑤
        R_DOWN  = 1 << 7,   //���̉���
    };
    const int block_size(12);   //�u���b�N�̉��E�c��

    const std::string   def_task  ("�}�b�v"); //�^�X�N��

    //----------------------------------------------
    class Resource
    {
    private:
        static std::weak_ptr<Resource> instance_;

    public:
        std::string map_chip_;

        Resource();     //�R���X�g���N�^
        ~Resource();    //�f�X�g���N�^
        static std::shared_ptr<Resource> Create();  //���\�[�X�̐���
    };

    //----------------------------------------------
    class Task : public TaskAbstract
    {
    private:
        std::shared_ptr<Resource> res_; //�m�ۂ������\�[�X

        int size_, width_, height_;
        ImageDrawer chip_image_;

        std::vector<std::vector<int>>           map_data_;  //�}�b�v�f�[�^
        std::vector<std::vector<Math::Box2D>>   map_rect_;  //�}�b�v��`

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

        //�}�b�v�Ƌ�`�̓����蔻����s���A�ڐG���Ă���u���b�N�̓�����Ԃ�
        BlockTrait GetHitBlockTrait(const Math::Box2D& rect);
        //�n�ʂƋ�`�����Ƃ̐ڐG������s���A�ʏ�u���b�N���ڐG���Ă���ꍇtrue��Ԃ�
        bool IsHitFoot(const Math::Box2D& rect);
        //��`�̎��͂Ɏw��u���b�N���ڐG���Ă���ꍇ�A���̐ڐG�ʒu��Ԃ�(�����ڐG���Ă���ꍇ��Non)
        RectGirth GetHitRectGirth(const Math::Box2D& rect, BlockTrait block_trait);

    private:
        //�}�b�v�f�[�^��ǂݍ���
        void LoadMapData(const std::string& map_data_path);
        //�}�b�v�f�[�^���폜����
        void DeleteMapData();
        //������́u,�v�𔼊p�X�y�[�X�ɒu�����Astringstream��Ԃ�
        std::stringstream ReplaceStrComma(const std::string& str);
    };
}