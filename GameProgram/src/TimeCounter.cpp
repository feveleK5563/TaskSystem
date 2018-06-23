#include "TimeCounter.h"

TimeCounter::TimeCounter():
	cntTime(0),
	endTime(-1),
	isTimeEnd(false) {}

TimeCounter::TimeCounter(int endTime):
	cntTime(0),
	endTime(endTime),
	isTimeEnd(false) {}

//経過時間を0にする
void TimeCounter::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

//終了時間を設定する
void TimeCounter::SetEndTime(int setEndTime)
{
	endTime = setEndTime;
	isTimeEnd = false;
}

//時間を測る
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

//現在の経過時間を返す
int TimeCounter::GetNowCntTime() const
{
	return cntTime;
}

//経過時間が終了時間まで到達していたらtrueを返す
bool TimeCounter::IsTimeEnd() const
{
	return isTimeEnd;
}