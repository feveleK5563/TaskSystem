#include <iostream>
#include <math.h>
#include <assert.h>
#include "DxLib.h"
#include "InputState.h"
#include "UtilityFunctions.h"

//-----------------------------------------------------------------------------
//�R���X�g���N�^
InputDXL::ButtonInfo::ButtonInfo() :
	durationTime(0),
	state(OFF) {}

//-----------------------------------------------------------------------------
//��Ԃ̐ݒ�Ə�Ԏ������Ԃ̌v��
void InputDXL::ButtonInfo::SetState(const InputState& setState)
{
	if (state == setState)
	{
		++durationTime;
	}
	else
	{
		durationTime = 0;
	}
	state = setState;
}

//-----------------------------------------------------------------------------
//���͏󋵂����Ԃ�ݒ�
void InputDXL::ButtonInfo::AutoSetState(const bool isButtonOn)
{
	if (isButtonOn)
	{
		if (state == DOWN || state == ON)
		{
			SetState(ON);
		}
		else
		{
			SetState(DOWN);
		}
	}
	else
	{
		if (state == UP || state == OFF)
		{
			SetState(OFF);
		}
		else
		{
			SetState(UP);
		}
	}
}

//-----------------------------------------------------------------------------
//��Ԏ������Ԃ��擾
int InputDXL::ButtonInfo::GetDurationTime(const InputState& instate) const
{
	if (state == instate)
	{
		return durationTime;
	}

	return -1;
}

//-----------------------------------------------------------------------------
//��Ԃ̔�r(��v)
bool InputDXL::ButtonInfo::operator ==(const InputState& instate) const
{
	return state == instate;
}

//-----------------------------------------------------------------------------
//��Ԃ̔�r(�s��v)
bool InputDXL::ButtonInfo::operator!=(const InputState& instate) const
{
	return state != instate;
}


//-----------------------------------------------------------------------------
//�R���X�g���N�^
InputDXL::MouseInput::MouseInput():
	pos(0.f, 0.f),
	isInput(false){}

//-----------------------------------------------------------------------------
//�}�E�X���͏����󂯎��
bool InputDXL::MouseInput::GetInputState()
{
	int state = GetMouseInput();
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(state & (1 << i));
	}
	isInput = state > 0;

	int x, y;
	GetMousePoint(&x, &y);
	pos.x = (float)x;
	pos.y = (float)y;

	return true;
}
//-----------------------------------------------------------------------------
//�}�E�X�̍��W���擾����
const MATH::Vec2& InputDXL::MouseInput::GetPos() const
{
	return pos;
}
//-----------------------------------------------------------------------------
//���炩�̓��͂����������ۂ�
bool InputDXL::MouseInput::IsInput() const
{
	return isInput;
}
//-----------------------------------------------------------------------------
//�w��{�^���̎����͏����擾����
const InputDXL::ButtonInfo& InputDXL::MouseInput::operator [](const MouseButton INPUT_TYPE) const
{
	return keyInfo[(int)INPUT_TYPE];
}


//-----------------------------------------------------------------------------
//�L�[���͏����󂯎��
bool InputDXL::KeyInput::GetInputState()
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
//���炩�̓��͂����������ۂ�
bool InputDXL::KeyInput::IsInput() const
{
	return CheckHitKeyAll() == 0;
}
//-----------------------------------------------------------------------------
//�w��L�[�̎����͏����擾����
const InputDXL::ButtonInfo& InputDXL::KeyInput::operator [](const int KEY_INPUT) const
{
	return keyInfo[KEY_INPUT];
}


//-----------------------------------------------------------------------------
//�R���X�g���N�^(�W���C�p�b�h�̔ԍ���ݒ肷��)
InputDXL::PadInput::PadInput(unsigned int id):
	inputId(id),
	isInput(false){}

//-----------------------------------------------------------------------------
//�W���C�p�b�h�̓��͏����󂯎��
bool InputDXL::PadInput::GetInputState()
{
	int state = GetJoypadInputState(inputId);
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(state & (1 << i));
	}
	isInput = state > 0;

	int lx, ly, rx, ry;
	GetJoypadAnalogInput(&lx, &ly, inputId);
	GetJoypadAnalogInputRight(&rx, &ry, inputId);
	analogInputLX = float(lx) / 1000.f;
	analogInputLY = float(ly) / 1000.f;
	analogInputRX = float(rx) / 1000.f;
	analogInputRY = float(ry) / 1000.f;

	return true;
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̊p�x���擾����
float InputDXL::PadInput::GetAngleStickL() const
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̊p�x���擾����
float InputDXL::PadInput::GetAngleStickR() const
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//���X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickL() const
{
	return min(std::sqrtf(analogInputLX * analogInputLX + analogInputLY * analogInputLY), 1.f);
}
//-----------------------------------------------------------------------------
//�E�X�e�B�b�N�̌X�����擾����(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickR() const
{
	return min(std::sqrtf(analogInputRX * analogInputRX + analogInputRY * analogInputRY), 1.f);
}
//-----------------------------------------------------------------------------
//���炩�̓��͂����������ۂ�
bool InputDXL::PadInput::IsInput() const
{
	return isInput;
}
//-----------------------------------------------------------------------------
//�w��{�^���̓��͏����擾����
const InputDXL::ButtonInfo& InputDXL::PadInput::operator [](const PadButton INPUT_TYPE) const
{
	return keyInfo[(int)INPUT_TYPE];
}



InputDXL::MouseInput* InputDXL::mouse = nullptr;
//-----------------------------------------------------------------------------
//�}�E�X�̃C���X�^���X���擾
const InputDXL::MouseInput& InputDXL::GetMouse()
{
	assert(mouse != nullptr && "MouseInput hasn't been created!");
	return *mouse;
}
//-----------------------------------------------------------------------------
//�}�E�X�̃C���X�^���X�𐶐�
void InputDXL::CreateMouseInstance()
{
	if (mouse == nullptr)
	{
		mouse = new MouseInput();
	}
}
//-----------------------------------------------------------------------------
//�}�E�X�̃C���X�^���X���������
void InputDXL::DeleteMouseInstance()
{
	UTIL::SafeDelete(mouse);
}
//-----------------------------------------------------------------------------
//�}�E�X�̓��͏����擾����
bool InputDXL::GetMouseInputState()
{
	if (mouse == nullptr)	return true;
	return mouse->GetInputState();
}

InputDXL::KeyInput* InputDXL::key = nullptr;
//-----------------------------------------------------------------------------
//�L�[�{�[�h�̃C���X�^���X���擾
const InputDXL::KeyInput& InputDXL::GetKey()
{
	assert(key != nullptr && "KeyInput hasn't been created!");
	return *key;
}
//-----------------------------------------------------------------------------
//�L�[�{�[�h�̃C���X�^���X�𐶐�
void InputDXL::CreateKeyInstance()
{
	if (key == nullptr)
	{
		key = new KeyInput();
	}
}
//-----------------------------------------------------------------------------
//�L�[�{�[�h�̃C���X�^���X���������
void InputDXL::DeleteKeyInstance()
{
	UTIL::SafeDelete(key);
}
//-----------------------------------------------------------------------------
//�L�[�{�[�h�̓��͏����擾����
bool InputDXL::GetKeyInputState()
{
	if (key == nullptr)	return true;
	return key->GetInputState();
}

std::vector<InputDXL::PadInput*> InputDXL::pad;
//-----------------------------------------------------------------------------
//�W���C�p�b�h�̃C���X�^���X���擾
const InputDXL::PadInput& InputDXL::GetPad(unsigned int id)
{
	assert(pad.size() >= id && "PadInput hasn't been created!");
	return *pad[id];
}
//-----------------------------------------------------------------------------
//�W���C�p�b�h�̃C���X�^���X�𐶐�
void InputDXL::CreatePadInstance(unsigned int padNum)
{
	DeletePadInstance();

	pad.resize(padNum);
	for (unsigned int i = 0; i < padNum; ++i)
	{
		pad[i] = new PadInput(i + 1);
	}
}
//-----------------------------------------------------------------------------
//�W���C�p�b�h�̃C���X�^���X���������
void InputDXL::DeletePadInstance()
{
	for (auto& it : pad)
	{
		UTIL::SafeDelete(it);
	}
}
//-----------------------------------------------------------------------------
//�W���C�p�b�h�̓��͏���S�Ď擾����
bool InputDXL::GetPadAllInputState()
{
	bool isCompleteInput = true;
	for (auto& it : pad)
	{
		isCompleteInput = isCompleteInput && it->GetInputState();
	}
	return isCompleteInput;
}

//-----------------------------------------------------------------------------
//���͏����擾
bool InputDXL::GetAllInputState()
{
	return	GetMouseInputState() &&
			GetKeyInputState() &&
			GetPadAllInputState();
}

//-----------------------------------------------------------------------------
//���������S�ẴC���X�^���X�����
void InputDXL::DeleteAllInstance()
{
	DeleteMouseInstance();
	DeleteKeyInstance();
	DeletePadInstance();
}