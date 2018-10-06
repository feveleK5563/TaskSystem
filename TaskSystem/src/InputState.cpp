#include <iostream>
#include <math.h>
#include <assert.h>
#include "DxLib.h"
#include "InputState.h"
#include "UtilityFunctions.h"

//-----------------------------------------------------------------------------
//コンストラクタ
InputDXL::ButtonInfo::ButtonInfo() :
	durationTime(0),
	state(OFF) {}

//-----------------------------------------------------------------------------
//状態の設定と状態持続時間の計測
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
//入力状況から状態を設定
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
//状態持続時間を取得
int InputDXL::ButtonInfo::GetDurationTime(const InputState& instate) const
{
	if (state == instate)
	{
		return durationTime;
	}

	return -1;
}

//-----------------------------------------------------------------------------
//状態の比較(一致)
bool InputDXL::ButtonInfo::operator ==(const InputState& instate) const
{
	return state == instate;
}

//-----------------------------------------------------------------------------
//状態の比較(不一致)
bool InputDXL::ButtonInfo::operator!=(const InputState& instate) const
{
	return state != instate;
}


//-----------------------------------------------------------------------------
//コンストラクタ
InputDXL::MouseInput::MouseInput():
	pos(0.f, 0.f){}

//-----------------------------------------------------------------------------
//マウス入力情報を受け取る
bool InputDXL::MouseInput::GetInputState()
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
const InputDXL::ButtonInfo& InputDXL::MouseInput::operator [](const MouseButton INPUT_TYPE) const
{
	return keyInfo[(int)INPUT_TYPE];
}
//-----------------------------------------------------------------------------
//マウスの座標を取得する
const MATH::Vec2& InputDXL::MouseInput::GetPos() const
{
	return pos;
}


//-----------------------------------------------------------------------------
//キー入力情報を受け取る
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
//指定キーの持つ入力情報を取得する
const InputDXL::ButtonInfo& InputDXL::KeyInput::operator [](const int KEY_INPUT) const
{
	return keyInfo[KEY_INPUT];
}


//-----------------------------------------------------------------------------
//コンストラクタ(ジョイパッドの番号を設定する)
InputDXL::PadInput::PadInput(unsigned int id):
	inputId(id){}

//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を受け取る
bool InputDXL::PadInput::GetInputState()
{
	int state = GetJoypadInputState(inputId);
	for (int i = 0; i < keyNum; ++i)
	{
		keyInfo[i].AutoSetState(state & (1 << i));
	}

	int lx, ly, rx, ry;
	GetJoypadAnalogInput(&lx, &ly, inputId);
	GetJoypadAnalogInputRight(&rx, &ry, inputId);
	analogInputLX = (float)lx;
	analogInputLY = (float)ly;
	analogInputRX = (float)rx;
	analogInputRY = (float)ry;

	return true;
}
//-----------------------------------------------------------------------------
//左スティックの角度を取得する
float InputDXL::PadInput::GetAngleStickL() const
{
	return atan2f(analogInputLY, analogInputLX);
}
//-----------------------------------------------------------------------------
//右スティックの角度を取得する
float InputDXL::PadInput::GetAngleStickR() const
{
	return atan2f(analogInputRY, analogInputRX);
}
//-----------------------------------------------------------------------------
//左スティックの傾きを取得する(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickL() const
{
	return (analogInputLX * analogInputLX + analogInputLY * analogInputLY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//右スティックの傾きを取得する(0.0f~1.0f)
float InputDXL::PadInput::GetVolumeStickR() const
{
	return (analogInputRX * analogInputRX + analogInputRY * analogInputRY) / (1000.f * 1000.f);
}
//-----------------------------------------------------------------------------
//指定ボタンの入力情報を取得する
const InputDXL::ButtonInfo& InputDXL::PadInput::operator [](const PadButton INPUT_TYPE) const
{
	return keyInfo[(int)INPUT_TYPE];
}



InputDXL::MouseInput* InputDXL::mouse = nullptr;
//-----------------------------------------------------------------------------
//マウスのインスタンスを取得
const InputDXL::MouseInput& InputDXL::GetMouse()
{
	assert(mouse != nullptr);
	return *mouse;
}
//-----------------------------------------------------------------------------
//マウスのインスタンスを生成
void InputDXL::CreateMouseInstance()
{
	if (mouse == nullptr)
	{
		mouse = new MouseInput();
	}
}
//-----------------------------------------------------------------------------
//マウスのインスタンスを解放する
void InputDXL::DeleteMouseInstance()
{
	UTIL::SafeDelete(mouse);
}
//-----------------------------------------------------------------------------
//マウスの入力情報を取得する
bool InputDXL::GetMouseInputState()
{
	if (mouse == nullptr)	return true;
	return mouse->GetInputState();
}

InputDXL::KeyInput* InputDXL::key = nullptr;
//-----------------------------------------------------------------------------
//キーボードのインスタンスを取得
const InputDXL::KeyInput& InputDXL::GetKey()
{
	assert(key != nullptr);
	return *key;
}
//-----------------------------------------------------------------------------
//キーボードのインスタンスを生成
void InputDXL::CreateKeyInstance()
{
	if (key == nullptr)
	{
		key = new KeyInput();
	}
}
//-----------------------------------------------------------------------------
//キーボードのインスタンスを解放する
void InputDXL::DeleteKeyInstance()
{
	UTIL::SafeDelete(key);
}
//-----------------------------------------------------------------------------
//キーボードの入力情報を取得する
bool InputDXL::GetKeyInputState()
{
	if (key == nullptr)	return true;
	return key->GetInputState();
}

std::vector<InputDXL::PadInput*> InputDXL::pad;
//-----------------------------------------------------------------------------
//ジョイパッドのインスタンスを取得
const InputDXL::PadInput& InputDXL::GetPad(unsigned int id)
{
	assert(pad.size() > id);
	return *pad[id];
}
//-----------------------------------------------------------------------------
//ジョイパッドのインスタンスを生成
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
//ジョイパッドのインスタンスを解放する
void InputDXL::DeletePadInstance()
{
	for (auto& it : pad)
	{
		UTIL::SafeDelete(it);
	}
}
//-----------------------------------------------------------------------------
//ジョイパッドの入力情報を全て取得する
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
//入力情報を取得
bool InputDXL::GetAllInputState()
{
	return	GetMouseInputState() &&
			GetKeyInputState() &&
			GetPadAllInputState();
}

//-----------------------------------------------------------------------------
//生成した全てのインスタンスを解放
void InputDXL::DeleteAllInstance()
{
	DeleteMouseInstance();
	DeleteKeyInstance();
	DeletePadInstance();
}