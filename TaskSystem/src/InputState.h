#pragma once
#include "DxLib.h"
#include "ButtonInfo.h"
#include "Math.h"

//-----------------------------------------------------------------------------
//マウスの入力情報を保持する
class MouseInput
{
public:
	enum struct Type
	{
		LEFT	= 0,
		RIGHT	= 1,
		MIDDLE	= 2,
	};
private:
	static const int keyNum = 3;
	ButtonInfo keyInfo[keyNum];
	MATH::Vec2 pos;

	MouseInput();

public:
	bool GetInputStateAll();
	const ButtonInfo& operator [](const Type INPUT_TYPE);
	const MATH::Vec2& GetPos();

	static MouseInput& GetInstance();
};

//-----------------------------------------------------------------------------
//キーボードの入力情報を保持する
class KeyInput
{
private:
	static const int keyNum = 256;
	ButtonInfo keyInfo[keyNum];

	KeyInput() = default;

public:
	bool GetInputStateAll();
	const ButtonInfo& operator [](const int KEY_INPUT);

	static KeyInput& GetInstance();
};

//-----------------------------------------------------------------------------
//ゲームパッドの入力情報を保持する
class PadInput
{
public:
	enum struct Type
	{
		DOWN	= 0,
		LEFT	= 1,
		RIGHT	= 2,
		UP		= 3,
		A		= 4,
		B		= 5,
		X		= 6,
		Y		= 7,
		L1		= 8,
		R1		= 9,
		SELECT	= 10,
		START	= 11,
		L3		= 12,
		R3		= 13,
	};
private:
	static const int keyNum = 28;

	int inputType;
	ButtonInfo keyInfo[keyNum];
	float	analogInputLX, analogInputLY,
			analogInputRX, analogInputRY;

	PadInput(int type);

public:
	bool GetInputStateAll();
	float GetAngleStickL();
	float GetAngleStickR();
	float GetVolumeStickL();
	float GetVolumeStickR();

	const ButtonInfo& operator [](const Type INPUT_TYPE);

	static PadInput& GetInstance(int type);
};

//-----------------------------------------------------------------------------
// ゲーム内で使用する奴を以下に追加
//-----------------------------------------------------------------------------
namespace INPUT_DXL
{
	static MouseInput& mouse = MouseInput::GetInstance();
	static KeyInput& key = KeyInput::GetInstance();
	static PadInput& joypad1 = PadInput::GetInstance(DX_INPUT_PAD1);

	//入力情報を取得
	bool GetInputStateAll();
}