#pragma once
#include <vector>
#include "DxLib.h"
#include "Math.h"

enum InputState
{
	ON,		//������Ă���
	OFF,	//������Ă��Ȃ�
	DOWN,	//�������u��
	UP,		//�������u��
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
	//���͏��̊Ǘ�
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
	//�}�E�X�̓��͏���ێ�����
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

		const MATH::Vec2& GetPos() const;	//�}�E�X�|�C���^�̍��W���擾
		bool IsInput() const;				//���炩�̓��͂����������ۂ�

		const ButtonInfo& operator [](const MouseButton INPUT_TYPE) const;
	};

	//-----------------------------------------------------------------------------
	//�L�[�{�[�h�̓��͏���ێ�����
	class KeyInput
	{
	private:
		static const int keyNum = 256;
		ButtonInfo keyInfo[keyNum];

	public:
		KeyInput() = default;

		bool GetInputState();

		bool IsInput() const;	//���炩�̓��͂����������ۂ�

		const ButtonInfo& operator [](const int KEY_INPUT) const;
	};

	//-----------------------------------------------------------------------------
	//�Q�[���p�b�h�̓��͏���ێ�����
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

		float GetAngleStickL() const;	//���X�e�B�b�N�̊p�x���擾
		float GetAngleStickR() const;	//�E�X�e�B�b�N�̊p�x���擾
		float GetVolumeStickL() const;	//���X�e�B�b�N�̌X���̑傫�����擾
		float GetVolumeStickR() const;	//�E�X�e�B�b�N�̌X���̑傫�����擾
		bool IsInput() const;			//���炩�̓��͂����������ۂ�

		const ButtonInfo& operator [](const PadButton INPUT_TYPE) const;
	};

	static MouseInput* mouse;
	static KeyInput* key;
	static std::vector<PadInput*> pad;

public:
	//�}�E�X�̃C���X�^���X���擾
	static const MouseInput& GetMouse();
	//�}�E�X�̃C���X�^���X�𐶐�
	static void CreateMouseInstance();
	//�}�E�X�̃C���X�^���X�����
	static void DeleteMouseInstance();
	//�}�E�X�̓��͏����擾
	private: static bool GetMouseInputState();

public:
	//�L�[�{�[�h�̃C���X�^���X���擾
	static const KeyInput& GetKey();
	//�L�[�{�[�h�̃C���X�^���X�𐶐�
	static void CreateKeyInstance();
	//�L�[�{�[�h�̃C���X�^���X�����
	static void DeleteKeyInstance();
	//�L�[�{�[�h�̓��͏����擾
	private: static bool GetKeyInputState();

public:
	//�w��ԍ��̃W���C�p�b�h�̃C���X�^���X���擾
	static const PadInput& GetPad(unsigned int id);
	//�w����W���C�p�b�h�̃C���X�^���X�𐶐�
	static void CreatePadInstance(unsigned int padNum);
	//�W���C�p�b�h�̃C���X�^���X�����
	static void DeletePadInstance();
	//�W���C�p�b�h�̓��͏���S�Ď擾
	private: static bool GetPadAllInputState();

public:
	//�S�Ă̓��͏����擾
	static bool GetAllInputState();

	//���������S�ẴC���X�^���X�����
	static void DeleteAllInstance();
};