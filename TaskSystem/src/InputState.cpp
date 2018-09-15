#include <math.h>
#include "DxLib.h"

#include "InputState.h"

//-----------------------------------------------------------------------------
//コンストラクタ
MouseInput::MouseInput():
	pos(0.f, 0.f){}

//-----------------------------------------------------------------------------
//マウス入力情報を受け取る
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
//指定ボタンの持つ入力情報を取得する
const ButtonInfo& MouseInput::operator [](const Type INPUT_TYPE)
{
	return keyInfo[(int)INPUT_TYPE];
}
//-----------------------------------------------------------------------------
//マウスの座標を取得する
const MATH::Vec2& MouseInput::GetPos()
{
	return pos;
}
//-----------------------------------------------------------------------------
//マウス入力情報のインスタンスを得る
MouseInput& MouseInput::GetInstance()
{
	static MouseInput mouse;
	return mouse;
}


//-----------------------------------------------------------------------------
//キー入力情報を受け取る
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
//指定キーの持つ入力情報を取得する
const ButtonInfo& KeyInput::operator [](const int KEY_INPUT)
{
	return keyInfo[KEY_INPUT];
}
//-----------------------------------------------------------------------------
//キー入力情報のインスタンスを得る
KeyInput& KeyInput::GetInstance()
{
	static KeyInput key;
	return key;
}


//-----------------------------------------------------------------------------
//コンストラクタ(ジョイパッドの番号を設定する)
PadInput::PadInput(int type):
	inputType(type){}

//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を受け取る
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
//左スティックの角度を取得する
float PadInput::GetAngleStickL()
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//右スティックの角度を取得する
float PadInput::GetAngleStickR()
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//左スティックの傾きを取得する(0.0f~1.0f)
float PadInput::GetVolumeStickL()
{
	return (analogInputLX * analogInputLX + analogInputLY * analogInputLY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//右スティックの傾きを取得する(0.0f~1.0f)
float PadInput::GetVolumeStickR()
{
	return (analogInputRX * analogInputRX + analogInputRY * analogInputRY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//指定ボタンの入力情報を取得する
const ButtonInfo& PadInput::operator [](const Type INPUT_TYPE)
{
	return keyInfo[(int)INPUT_TYPE];
}
//-----------------------------------------------------------------------------
//ゲームパッド入力情報のインスタンスを得る
PadInput& PadInput::GetInstance(int type)
{
	static PadInput joypad(type);
	return joypad;
}


//-----------------------------------------------------------------------------
// ゲーム内で使用する奴を以下に追加
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//入力情報を取得
bool INPUT_DXL::GetInputStateAll()
{
	return	mouse.GetInputStateAll()	&&
			key.GetInputStateAll()		&&
			joypad1.GetInputStateAll();
}