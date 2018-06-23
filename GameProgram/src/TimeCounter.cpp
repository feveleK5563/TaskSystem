#include "TimeCounter.h"

TimeCounter::TimeCounter():
	cntTime(0),
	endTime(-1),
	isTimeEnd(false) {}

TimeCounter::TimeCounter(int endTime):
	cntTime(0),
	endTime(endTime),
	isTimeEnd(false) {}

//�o�ߎ��Ԃ�0�ɂ���
void TimeCounter::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

//�I�����Ԃ�ݒ肷��
void TimeCounter::SetEndTime(int setEndTime)
{
	endTime = setEndTime;
	isTimeEnd = false;
}

//���Ԃ𑪂�
void TimeCounter::Run()
{
	if (endTime >= 0 &&
		cntTime >= endTime)
	{
		isTimeEnd = true;
		return;
	}

	++cntTime;
}

//���݂̌o�ߎ��Ԃ�Ԃ�
int TimeCounter::GetNowCntTime() const
{
	return cntTime;
}

//�o�ߎ��Ԃ��I�����Ԃ܂œ��B���Ă�����true��Ԃ�
bool TimeCounter::IsTimeEnd() const
{
	return isTimeEnd;
}