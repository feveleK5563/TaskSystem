#include <math.h>
#include "DxLib.h"

#include "InputState.h"

//-----------------------------------------------------------------------------
//�L�[���͏����󂯎��
int KeyInput::GetInputStateAll()
{
	char getHitKeyStateAll_Key[keyNum];
	GetHitKeyStateAll(getHitKeyStateAll_Key);
	for (int i = 0; i < keyNum; i++)
	{
		keyInfo[i].AutoSetState(getHitKeyStateAll_Key[i]);
	}
	return 0;
}
//-----------------------------------------------------------------------------
//�w��L�[�̎����͏����擾����
const ButtonInfo& KeyInput::operator [](const int KEY_INPUT)
{
	return keyInfo[KEY_INPUT];
}
//-----------------------------------------------------------------------------
//�L�[���͏��̃C���X�^���X�𓾂�
KeyInput& KeyInput::GetInstance()
{
	static KeyInput key;
	return key;
}


//-----------------------------------------------------------------------------
//�R���X�g���N�^(�W���C�p�b�h�̔ԍ���ݒ肷��)
JoypadInput::JoypadInput(int type):
	inputType(type){}

//-----------------------------------------------------------------------------
//�W���C�p�b�h�̓��͏����󂯎��
int JoypadInput::GetInputStateAll()
{
	int state = GetJoypadInputState(inputType);
	for (int i = 0; i < padNum; ++i)
	{
		padInfo[i].AutoSetState(state & (1 << i));
	}

	int lx, ly, rx, ry;
	GetJoypadAnalogInput(&lx, &ly, inputType);
	GetJoypadAnalogInputRight(&rx, &ry, inputType);
	analogInputLX = (float)lx;
	analogInputLY = (float)ly;
	analogInputRX = (float)rx;
	analogInputRY = (float)ry;

	return 0;
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̊p�x���擾����
float JoypadInput::GetAngleStickL()
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̊p�x���擾����
float JoypadInput::GetAngleStickR()
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float JoypadInput::GetVolumeStickL()
{
	return (analogInputLX * analogInputLX + analogInputLY * analogInputLY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float JoypadInput::GetVolumeStickR()
{
	return (analogInputRX * analogInputRX + analogInputRY * analogInputRY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//�w��{�^���̓��͏����擾����
const ButtonInfo& JoypadInput::operator [](const PadInput PAD_INPUT)
{
	int padInput = int(log2f((float)PAD_INPUT));
	return padInfo[padInput];
}
//-----------------------------------------------------------------------------
//�Q�[���p�b�h���͏��̃C���X�^���X�𓾂�
JoypadInput& JoypadInput::GetInstance(int type)
{
	static JoypadInput joypad(type);
	return joypad;
}


//-----------------------------------------------------------------------------
// �Q�[�����Ŏg�p����z���ȉ��ɒǉ�
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//���͏����擾
bool Input::GetInputStateAll()
{
	return	key.GetInputStateAll()		== 0 &&
			joypad1.GetInputStateAll()	== 0;
}