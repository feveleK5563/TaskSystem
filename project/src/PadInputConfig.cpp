#include "PadInputConfig.h"
#include "Utility.h"

//�R���X�g���N�^
PadInputConfig::PadConfig::PadConfig(unsigned int id, bool use_pad, bool use_key):
    input_id_(id),
    use_pad_(use_pad),
    use_key_(use_key)
{
    pad_set_.resize(ButtonNum::pad);
    key_set_.resize(ButtonNum::pad + 8); //+8�̓X�e�B�b�N�̕�
    Initialize();
}

//-----------------------------------------------------------------------------
//�p�b�h�z�u��������
void PadInputConfig::PadConfig::Initialize()
{
    //�p�b�h�̃{�^�����蓖�Ă�ݒ�
    SetPadConfig(PAD_INPUT::LEFT, PAD_INPUT::LEFT);
    SetPadConfig(PAD_INPUT::RIGHT, PAD_INPUT::RIGHT);
    SetPadConfig(PAD_INPUT::UP, PAD_INPUT::UP);
    SetPadConfig(PAD_INPUT::DOWN, PAD_INPUT::DOWN);
    SetPadConfig(PAD_INPUT::A, PAD_INPUT::A);
    SetPadConfig(PAD_INPUT::B, PAD_INPUT::B);
    SetPadConfig(PAD_INPUT::X, PAD_INPUT::X);
    SetPadConfig(PAD_INPUT::Y, PAD_INPUT::Y);
    SetPadConfig(PAD_INPUT::L1, PAD_INPUT::L1);
    SetPadConfig(PAD_INPUT::R1, PAD_INPUT::R1);
    SetPadConfig(PAD_INPUT::SELECT, PAD_INPUT::SELECT);
    SetPadConfig(PAD_INPUT::START, PAD_INPUT::START);
    SetPadConfig(PAD_INPUT::L3, PAD_INPUT::L3);
    SetPadConfig(PAD_INPUT::R3, PAD_INPUT::R3);

    //�L�[���蓖�Ă�ݒ�
    SetPadConfig(PAD_INPUT::LEFT, KEY_INPUT::LEFT);
    SetPadConfig(PAD_INPUT::RIGHT, KEY_INPUT::RIGHT);
    SetPadConfig(PAD_INPUT::UP, KEY_INPUT::UP);
    SetPadConfig(PAD_INPUT::DOWN, KEY_INPUT::DOWN);
    SetPadConfig(PAD_INPUT::A, KEY_INPUT::Z);
    SetPadConfig(PAD_INPUT::B, KEY_INPUT::X);
    SetPadConfig(PAD_INPUT::X, KEY_INPUT::C);
    SetPadConfig(PAD_INPUT::Y, KEY_INPUT::V);
    SetPadConfig(PAD_INPUT::L1, KEY_INPUT::L);
    SetPadConfig(PAD_INPUT::R1, KEY_INPUT::R);
    SetPadConfig(PAD_INPUT::SELECT, KEY_INPUT::LALT);
    SetPadConfig(PAD_INPUT::START, KEY_INPUT::SPACE);
    SetPadConfig(PAD_INPUT::L3, KEY_INPUT::T);
    SetPadConfig(PAD_INPUT::R3, KEY_INPUT::K);
    SetLStickConfig(KEY_INPUT::A, KEY_INPUT::D, KEY_INPUT::W, KEY_INPUT::S);
    SetRStickConfig(KEY_INPUT::NUMPAD4, KEY_INPUT::NUMPAD6, KEY_INPUT::NUMPAD8, KEY_INPUT::NUMPAD2);
}

//-----------------------------------------------------------------------------
//�p�b�h�z�u��ύX
void PadInputConfig::PadConfig::SetPadConfig(PAD_INPUT target, PAD_INPUT set)
{
    pad_set_[(int)target] = set;
}
//�p�b�h�̃L�[���蓖�Ă�ύX
void PadInputConfig::PadConfig::SetPadConfig(PAD_INPUT target, KEY_INPUT set)
{
    key_set_[(int)target] = set;
}
//���X�e�B�b�N�̃L�[���蓖�Ă�ύX
void PadInputConfig::PadConfig::SetLStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d)
{
    for (int i = ButtonNum::pad; i < ButtonNum::pad + 4; ++i)
    {
        switch (i - ButtonNum::pad)
        {
        case 0: key_set_[i] = l; break;
        case 1: key_set_[i] = r; break;
        case 2: key_set_[i] = u; break;
        case 3: key_set_[i] = d; break;
        }
    }
}
//�E�X�e�B�b�N�̃L�[���蓖�Ă�ύX
void PadInputConfig::PadConfig::SetRStickConfig(KEY_INPUT l, KEY_INPUT r, KEY_INPUT u, KEY_INPUT d)
{
    for (int i = ButtonNum::pad + 4; i < ButtonNum::pad + 8; ++i)
    {
        switch (i - ButtonNum::pad)
        {
        case 4: key_set_[i] = l; break;
        case 5: key_set_[i] = r; break;
        case 6: key_set_[i] = u; break;
        case 7: key_set_[i] = d; break;
        }
    }
}

//-----------------------------------------------------------------------------
//�L�[�A�p�b�h�A���҂��瓾������͏�Ԃ𓝍����ĕԂ�
InputState PadInputConfig::PadConfig::GetState(PAD_INPUT target) const
{
    InputState ps = OFF, ks = OFF;
    if (use_pad_)
    {
        ps = InputDXL::GetPad(input_id_)[pad_set_[(int)target]].GetInputState();
    }
    if (use_key_)
    {
        ks = InputDXL::GetKey()[key_set_[(int)target]].GetInputState();
    }

    //���҂���������Ȃ炻�̂܂ܕԂ�
    if (ps == ks) { return ps; }

    //���҂̔��肪�قȂ�ꍇ�A�D��x���� ON, DOWN, UP, OFF �𔻒肷��
    if (ps == ON || ks == ON)       { return ON; }
    if (ps == DOWN || ks == DOWN)   { return DOWN; }

    return UP;
}
//���X�e�B�b�N�̃x�N�g�����擾����
Math::Vec2 PadInputConfig::PadConfig::GetVecStickL() const
{
    Math::Vec2 vp, vk;
    if (use_pad_)
    {
        vp = InputDXL::GetPad(input_id_).GetVecStickL();
    }
    if (use_key_)
    {
        auto& ks = InputDXL::GetKey();
        if (ks[key_set_[ButtonNum::pad + 0]] == ON ||
            ks[key_set_[ButtonNum::pad + 0]] == DOWN) { vk.x -= 1; }
        if (ks[key_set_[ButtonNum::pad + 1]] == ON ||
            ks[key_set_[ButtonNum::pad + 1]] == DOWN) { vk.x += 1; }
        if (ks[key_set_[ButtonNum::pad + 2]] == ON ||
            ks[key_set_[ButtonNum::pad + 2]] == DOWN) { vk.y -= 1; }
        if (ks[key_set_[ButtonNum::pad + 3]] == ON ||
            ks[key_set_[ButtonNum::pad + 3]] == DOWN) { vk.y += 1; }
    }

    if (vp.GetDistance() >= vk.GetDistance())
    {
        return vp;
    }
    else
    {
        vk.Normalize();
        return vk;
    }
}
//�E�X�e�B�b�N�̃x�N�g�����擾����
Math::Vec2 PadInputConfig::PadConfig::GetVecStickR() const
{
    Math::Vec2 vp, vk;
    if (use_pad_)
    {
        vp = InputDXL::GetPad(input_id_).GetVecStickR();
    }
    if (use_key_)
    {
        auto& ks = InputDXL::GetKey();
        if (ks[key_set_[ButtonNum::pad + 4]] == ON ||
            ks[key_set_[ButtonNum::pad + 4]] == DOWN) { vk.x -= 1; }
        if (ks[key_set_[ButtonNum::pad + 5]] == ON ||
            ks[key_set_[ButtonNum::pad + 5]] == DOWN) { vk.x += 1; }
        if (ks[key_set_[ButtonNum::pad + 6]] == ON ||
            ks[key_set_[ButtonNum::pad + 6]] == DOWN) { vk.y -= 1; }
        if (ks[key_set_[ButtonNum::pad + 7]] == ON ||
            ks[key_set_[ButtonNum::pad + 7]] == DOWN) { vk.y += 1; }
    }

    if (vp.GetDistance() >= vk.GetDistance())
    {
        return vp;
    }
    else
    {
        vk.Normalize();
        return vk;
    }
}

//-----------------------------------------------------------------------------

std::vector<PadInputConfig::PadConfig*> PadInputConfig::config;
//�Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X�擾
PadInputConfig::PadConfig& PadInputConfig::GetInstance(unsigned int id)
{
    assert(IsCreatedInstance(id) && "PadInputConfig hasn't been created!");
    return *config[id];
}
//�Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X����
void PadInputConfig::CreateInstance(unsigned int pad_num, bool use_pad, bool use_key)
{
    DeleteInstance();
    config.resize(pad_num);
    for (unsigned int i = 0; i < pad_num; ++i)
    {
        config[i] = new PadConfig(i, use_pad, use_key);
    }
}
//�Q�[���p�b�h�R���t�B�O�}���̃C���X�^���X�폜
void PadInputConfig::DeleteInstance()
{
    if (config.size() <= 0) { return; }

    for (auto& it : config)
    {
        Util::SafeDelete(it);
    }
    config.clear();
    config.shrink_to_fit();
}
//�w��ԍ��̃Q�[���p�b�h�R���t�B�O�}������������Ă��邩�ۂ����擾
bool PadInputConfig::IsCreatedInstance(unsigned int id)
{
    if (id >= config.size()) { return false; }
    return true;
}