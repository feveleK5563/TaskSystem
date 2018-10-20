#pragma once
#include <vector>
#include "DxLib.h"
#include "Math.h"

enum InputState
{
	ON,		//押されている
	OFF,	//押されていない
	DOWN,	//押した瞬間
	UP,		//離した瞬間
};

enum struct MouseButton
{
	LEFT	= 0,
	RIGHT	= 1,
	MIDDLE	= 2,
};

enum struct PadButton
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

class InputDXL
{
private:
	//-----------------------------------------------------------------------------
	//入力情報の管理
	class ButtonInfo
	{
	private:
		int durationTime;
		InputState state;

	public:
		ButtonInfo();
		void SetState(const InputState& setState);
		void AutoSetState(const bool isButtonOn);

		int GetDurationTime(const InputState& instate) const;
		bool operator ==(const InputState& instate) const;
		bool operator !=(const InputState& instate) const;
	};

	//-----------------------------------------------------------------------------
	//マウスの入力情報を保持する
	class MouseInput
	{
	private:
		static const int keyNum = 3;
		ButtonInfo keyInfo[keyNum];
		MATH::Vec2 pos;
		bool isInput;

	public:
		MouseInput();

		bool GetInputState();

		const MATH::Vec2& GetPos() const;	//マウスポインタの座標を取得
		bool IsInput() const;				//何らかの入力があったか否か

		const ButtonInfo& operator [](const MouseButton INPUT_TYPE) const;
	};

	//-----------------------------------------------------------------------------
	//キーボードの入力情報を保持する
	class KeyInput
	{
	private:
		static const int keyNum = 256;
		ButtonInfo keyInfo[keyNum];

	public:
		KeyInput() = default;

		bool GetInputState();

		bool IsInput() const;	//何らかの入力があったか否か

		const ButtonInfo& operator [](const int KEY_INPUT) const;
	};

	//-----------------------------------------------------------------------------
	//ゲームパッドの入力情報を保持する
	class PadInput
	{
	private:
		static const int keyNum = 28;

		unsigned int inputId;
		ButtonInfo keyInfo[keyNum];
		float	analogInputLX, analogInputLY,
				analogInputRX, analogInputRY;
		bool isInput;

	public:
		PadInput(unsigned int id);

		bool GetInputState();

		float GetAngleStickL() const;	//左スティックの角度を取得
		float GetAngleStickR() const;	//右スティックの角度を取得
		float GetVolumeStickL() const;	//左スティックの傾きの大きさを取得
		float GetVolumeStickR() const;	//右スティックの傾きの大きさを取得
		bool IsInput() const;			//何らかの入力があったか否か

		const ButtonInfo& operator [](const PadButton INPUT_TYPE) const;
	};

	static MouseInput* mouse;
	static KeyInput* key;
	static std::vector<PadInput*> pad;

public:
	//マウスのインスタンスを取得
	static const MouseInput& GetMouse();
	//マウスのインスタンスを生成
	static void CreateMouseInstance();
	//マウスのインスタンスを解放
	static void DeleteMouseInstance();
	//マウスの入力情報を取得
	private: static bool GetMouseInputState();

public:
	//キーボードのインスタンスを取得
	static const KeyInput& GetKey();
	//キーボードのインスタンスを生成
	static void CreateKeyInstance();
	//キーボードのインスタンスを解放
	static void DeleteKeyInstance();
	//キーボードの入力情報を取得
	private: static bool GetKeyInputState();

public:
	//指定番号のジョイパッドのインスタンスを取得
	static const PadInput& GetPad(unsigned int id);
	//指定個数ジョイパッドのインスタンスを生成
	static void CreatePadInstance(unsigned int padNum);
	//ジョイパッドのインスタンスを解放
	static void DeletePadInstance();
	//ジョイパッドの入力情報を全て取得
	private: static bool GetPadAllInputState();

public:
	//全ての入力情報を取得
	static bool GetAllInputState();

	//生成した全てのインスタンスを解放
	static void DeleteAllInstance();
};