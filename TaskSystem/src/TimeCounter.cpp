#include "TimeCounter.h"

TimeCounter::TimeCounter():
	cntTime(0),
	endTime(-1),
	addVol(1),
	isTimeEnd(false) {}

TimeCounter::TimeCounter(int endTime):
	cntTime(0),
	endTime(endTime),
	addVol(1),
	isTimeEnd(false) {}

TimeCounter::TimeCounter(int endTime, int addVol):
	cntTime(0),
	endTime(endTime),
	addVol(addVol),
	isTimeEnd(false){}

//経過時間を0にする
void TimeCounter::ResetCntTime()
{
	cntTime = 0;
	isTimeEnd = false;
}

//終了時間を設定する
void TimeCounter::SetEndTime(int endTime)
{
	this->endTime = endTime;
	isTimeEnd = false;
}

//時間を測る
void TimeCounter::Run()
{
	if (endTime >= 0 &&
		cntTime >= endTime)
	{
		cntTime = endTime;
		isTimeEnd = true;
		return;
	}

	cntTime += addVol;
}

//現在の経過時間を返す
const int& TimeCounter::GetNowCntTime() const
{
	return cntTime;
}

//残り時間(終了時間-経過時間)を返す
int TimeCounter::GetRemainingTime() const
{
	return endTime - cntTime;
}

//終了時間を返す
const int& TimeCounter::GetEndTime() const
{
	return endTime;
}

//経過時間が終了時間まで到達していたらtrueを返す
const bool& TimeCounter::IsTimeEnd() const
{
	return isTimeEnd;
}

//-----------------------------------------------------------------------------

TimeCounterF::TimeCounterF() :
	cntTime(0.f),
	endTime(-1.f),
	addVol(1.f),
	isTimeEnd(false) {}

TimeCounterF::TimeCounterF(float endTime):
	cntTime(0.f),
	endTime(endTime),
	addVol(1.f),
	isTimeEnd(false) {}

TimeCounterF::TimeCounterF(float endTime, float addVol):
	cntTime(0.f),
	endTime(endTime),
	addVol(addVol),
	isTimeEnd(false) {}


//経過時間を0.fにする
void TimeCounterF::ResetCntTime()
{
	cntTime = 0.f;
	isTimeEnd = false;
}

//終了時間を設定する
void TimeCounterF::SetEndTime(float endTime)
{
	this->endTime = endTime;
	isTimeEnd = false;
}

//時間を測る
void TimeCounterF::Run()
{
	if (endTime >= 0.f &&
		cntTime >= endTime)
	{
		cntTime = endTime;
		isTimeEnd = true;
		return;
	}

	cntTime += addVol;
}

//現在の経過時間を返す
const float& TimeCounterF::GetNowCntTime() const
{
	return cntTime;
}

//残り時間(終了時間-経過時間)を返す
float TimeCounterF::GetRemainingTime() const
{
	return endTime - cntTime;
}

//終了時間を返す
const float& TimeCounterF::GetEndTime() const
{
	return endTime;
}

//経過時間が終了時間まで到達していたらtrueを返す
const bool& TimeCounterF::IsTimeEnd() const
{
	return isTimeEnd;
}