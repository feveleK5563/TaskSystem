#include <math.h>
#include "DxLib.h"

#include "InputState.h"

//-----------------------------------------------------------------------------
//キー入力情報を受け取る
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
JoypadInput::JoypadInput(int type):
	inputType(type){}

//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を受け取る
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
//左スティックの角度を取得する
float JoypadInput::GetAngleStickL()
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//右スティックの角度を取得する
float JoypadInput::GetAngleStickR()
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//左スティックの傾きを取得する(0.0f~1.0f)
float JoypadInput::GetVolumeStickL()
{
	return (analogInputLX * analogInputLX + analogInputLY * analogInputLY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//右スティックの傾きを取得する(0.0f~1.0f)
float JoypadInput::GetVolumeStickR()
{
	return (analogInputRX * analogInputRX + analogInputRY * analogInputRY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//指定ボタンの入力情報を取得する
const ButtonInfo& JoypadInput::operator [](const PadInput PAD_INPUT)
{
	int padInput = int(log2f((float)PAD_INPUT));
	return padInfo[padInput];
}
//-----------------------------------------------------------------------------
//ゲームパッド入力情報のインスタンスを得る
JoypadInput& JoypadInput::GetInstance(int type)
{
	static JoypadInput joypad(type);
	return joypad;
}


//-----------------------------------------------------------------------------
// ゲーム内で使用する奴を以下に追加
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//入力情報を取得
bool Input::GetInputStateAll()
{
	return	key.GetInputStateAll()		== 0 &&
			joypad1.GetInputStateAll()	== 0;
}