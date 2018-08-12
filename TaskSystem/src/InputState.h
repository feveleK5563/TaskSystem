#pragma once
#include "DxLib.h"
#include "ButtonInfo.h"

//-----------------------------------------------------------------------------
//�L�[�{�[�h�̓��͏���ێ�����
class KeyInput
{
private:
	static const int keyNum = 256;
	ButtonInfo keyInfo[keyNum];

	KeyInput() = default;

public:
	int GetInputStateAll();
	const ButtonInfo& operator [](const int KEY_INPUT);

	static KeyInput& GetInstance();
};

//-----------------------------------------------------------------------------
//�Q�[���p�b�h�̓��͏���ێ�����

enum struct PadInput
{
	DOWN	= 0x00000001,
	LEFT	= 0x00000002,
	RIGHT	= 0x00000004,
	UP		= 0x00000008,
	A		= 0x00000010,
	B		= 0x00000020,
	X		= 0x00000040,
	Y		= 0x00000080,
	L1		= 0x00000100,
	R1		= 0x00000200,
	SELECT	= 0x00000400,
	START	= 0x00000800,
	L3		= 0x00001000,
	R3		= 0x00002000,
};

class JoypadInput
{
private:
	static const int padNum = 28;

	int inputType;
	ButtonInfo padInfo[padNum];
	float	analogInputLX, analogInputLY,
			analogInputRX, analogInputRY;

	JoypadInput(int type);

public:
	int GetInputStateAll();
	float GetAngleStickL();
	float GetAngleStickR();
	float GetVolumeStickL();
	float GetVolumeStickR();

	const ButtonInfo& operator [](const PadInput PAD_INPUT);

	static JoypadInput& GetInstance(int type);
};

//-----------------------------------------------------------------------------
// �Q�[�����Ŏg�p����z���ȉ��ɒǉ�
//-----------------------------------------------------------------------------
namespace Input
{
	static KeyInput& key = KeyInput::GetInstance();
	static JoypadInput& joypad1 = JoypadInput::GetInstance(DX_INPUT_PAD1);

	//���͏����擾
	bool GetInputStateAll();
}