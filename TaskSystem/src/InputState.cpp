#include <math.h>
#include "DxLib.h"

#include "InputState.h"

//-----------------------------------------------------------------------------
//�R���X�g���N�^
MouseInput::MouseInput():
	pos(0.f, 0.f){}

//-----------------------------------------------------------------------------
//�}�E�X���͏����󂯎��
bool MouseInput::GetInputStateAll()
{
	int state = GetMouseInput();
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(state & (1 << i));
	}

	int x, y;
	GetMousePoint(&x, &y);
	pos.x = (float)x;
	pos.y = (float)y;

	return true;
}
//-----------------------------------------------------------------------------
//�w��{�^���̎����͏����擾����
const ButtonInfo& MouseInput::operator [](const Type INPUT_TYPE)
{
	return keyInfo[(int)INPUT_TYPE];
}
//-----------------------------------------------------------------------------
//�}�E�X�̍��W���擾����
const MATH::Vec2& MouseInput::GetPos()
{
	return pos;
}
//-----------------------------------------------------------------------------
//�}�E�X���͏��̃C���X�^���X�𓾂�
MouseInput& MouseInput::GetInstance()
{
	static MouseInput mouse;
	return mouse;
}


//-----------------------------------------------------------------------------
//�L�[���͏����󂯎��
bool KeyInput::GetInputStateAll()
{
	char getHitKeyStateAll_Key[keyNum];
	GetHitKeyStateAll(getHitKeyStateAll_Key);
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(getHitKeyStateAll_Key[i]);
	}
	return true;
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
PadInput::PadInput(int type):
	inputType(type){}

//-----------------------------------------------------------------------------
//�W���C�p�b�h�̓��͏����󂯎��
bool PadInput::GetInputStateAll()
{
	int state = GetJoypadInputState(inputType);
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(state & (1 << i));
	}

	int lx, ly, rx, ry;
	GetJoypadAnalogInput(&lx, &ly, inputType);
	GetJoypadAnalogInputRight(&rx, &ry, inputType);
	analogInputLX = (float)lx;
	analogInputLY = (float)ly;
	analogInputRX = (float)rx;
	analogInputRY = (float)ry;

	return true;
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̊p�x���擾����
float PadInput::GetAngleStickL()
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̊p�x���擾����
float PadInput::GetAngleStickR()
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float PadInput::GetVolumeStickL()
{
	return (analogInputLX * analogInputLX + analogInputLY * analogInputLY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float PadInput::GetVolumeStickR()
{
	return (analogInputRX * analogInputRX + analogInputRY * analogInputRY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//�w��{�^���̓��͏����擾����
const ButtonInfo& PadInput::operator [](const Type INPUT_TYPE)
{
	return keyInfo[(int)INPUT_TYPE];
}
//-----------------------------------------------------------------------------
//�Q�[���p�b�h���͏��̃C���X�^���X�𓾂�
PadInput& PadInput::GetInstance(int type)
{
	static PadInput joypad(type);
	return joypad;
}


//-----------------------------------------------------------------------------
// �Q�[�����Ŏg�p����z���ȉ��ɒǉ�
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//���͏����擾
bool INPUT_DXL::GetInputStateAll()
{
	return	mouse.GetInputStateAll()	&&
			key.GetInputStateAll()		&&
			joypad1.GetInputStateAll();
}