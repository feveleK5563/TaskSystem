#pragma once
#include "DxLib.h"
#include "ButtonInfo.h"

//-----------------------------------------------------------------------------
//キーボードの入力情報を保持する
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
//ゲームパッドの入力情報を保持する
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
	const ButtonInfo& operator [](const int PAD_INPUT);

	static JoypadInput& GetInstance(int type);
};

//-----------------------------------------------------------------------------
// ゲーム内で使用する奴を以下に追加
//-----------------------------------------------------------------------------
namespace Input
{
	static KeyInput& key = KeyInput::GetInstance();
	static JoypadInput& joypad1 = JoypadInput::GetInstance(DX_INPUT_KEY_PAD1);
}