#pragma once
#include <vector>
#include <array>
#include "InputDXL.h"

// �Q�[���p�b�h�R���t�B�O�}��(�Q�[�������͐ݒ�Ə�Ԃ̎擾)
class PadInputConfig
{
private:
    class PadConfig
    {
    private:
        const unsigned int input_id_;           // �ԍ�
        std::vector<PAD_INPUT> pad_set_;        // �Q�[���p�b�h�̃R���t�B�O
        std::vector<KEY_INPUT> key_set_;        // �L�[�{�[�h�̃R���t�B�O
        bool use_pad_;  // �p�b�h���g�p���邩�ۂ�
        bool use_key_;  // �L�[�{�[�h���g�p���邩�ۂ�

    public:
        // �R���X�g���N�^
        PadConfig(unsigned int id, bool use_pad, bool use_key);

        // �p�b�h�z�u��������
        void Initialize();
        // �p�b�h�z�u��ύX
        void SetPadConfig(PAD_INPUT target, PAD_INPUT set);
        // �p�b�h�̃L�[���蓖�Ă�ύX
        void SetPadConfig(PAD_INPUT target, KEY_INPUT set);
        // ���X�e�B�b�N�̃L�[���蓖�Ă�ύX
        void SetLStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d);
        // �E�X�e�B�b�N�̃L�[���蓖�Ă�ύX
        void SetRStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d);

        // �L�[�ƃp�b�h���瓾������͏�Ԃ𓝍����ĕԂ�
        InputState GetState(PAD_INPUT target) const;
        // ���X�e�B�b�N�̃x�N�g�����擾����
        Math::Vec2 GetVecStickL() const;
        // �E�X�e�B�b�N�̃x�N�g�����擾����
        Math::Vec2 GetVecStickR() const;
    };
    static std::vector<PadConfig*> config;

    PadInputConfig() = default;

public:
    // �Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X�擾
    static PadConfig& Get(unsigned int id);
    // �Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X����
    static void Create(unsigned int pad_num, bool use_pad, bool use_key);
    // �Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X�폜
    static void Delete();
    // �w��ԍ��̃Q�[���p�b�h�R���t�B�O�}������������Ă��邩�ۂ����擾
    static bool IsCreated(unsigned int id);
};