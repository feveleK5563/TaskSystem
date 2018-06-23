#pragma once

enum InputState
{
	ON,
	OFF,
	DOWN,
	UP,
};

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