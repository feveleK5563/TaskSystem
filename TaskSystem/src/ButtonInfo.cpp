#include "DxLib.h"

#include "ButtonInfo.h"

ButtonInfo::ButtonInfo() :
	durationTime(0),
	state(OFF) {}

void ButtonInfo::SetState(const InputState& setState)
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

void ButtonInfo::AutoSetState(const bool isButtonOn)
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

int ButtonInfo::GetDurationTime(const InputState& instate) const
{
	if (state == instate)
	{
		return durationTime;
	}

	return -1;
}

bool ButtonInfo::operator ==(const InputState& instate) const
{
	return state == instate;
}

bool ButtonInfo::operator!=(const InputState& instate) const
{
	return state != instate;
}
