#pragma once

//時間計測くん
class TimeCounter
{
private:
	int cntTime;	//経過時間
	int endTime;	//終了時間
	int addVol;		//加算する量
	bool isTimeEnd;	//終了時間以上計測しているか否か

public:
	//コンストラクタ(終了時間設定は無効)
	TimeCounter();
	//コンストラクタ(終了時間を指定(-1で無効))
	TimeCounter(int endTime);
	//コンストラクタ(終了時間と加算量を指定)
	TimeCounter(int endTime, int addVol);

	//経過時間を0にする
	void ResetCntTime();

	//終了時間を設定する(-1で無効)
	void SetEndTime(int endTime);

	//時間を測る
	//終了時間が有効の場合、その時間以上になったら停止する
	void Run();

	//現在の経過時間を返す
	const int& GetNowCntTime() const;

	//残り時間(終了時間-経過時間)を返す
	int GetRemainingTime() const;

	//終了時間を返す
	const int& GetEndTime() const;

	//経過時間が終了時間まで到達していたらtrueを返す
	const bool& IsTimeEnd() const;
};

//-----------------------------------------------------------------------------

//時間計測くん(floatバージョン)
class TimeCounterF
{
private:
	float	cntTime;	//経過時間
	float	endTime;	//終了時間
	float	addVol;		//加算する量
	bool	isTimeEnd;	//終了時間以上計測しているか否か

public:
	//コンストラクタ(終了時間設定は無効)
	TimeCounterF();
	//コンストラクタ(終了時間を指定(-1.fで無効))
	TimeCounterF(float endTime);
	//コンストラクタ(終了時間と加算量を指定)
	TimeCounterF(float endTime, float addVol);

	//経過時間を0.fにする
	void ResetCntTime();

	//終了時間を設定する(-1.fで無効)
	void SetEndTime(float endTime);

	//時間を測る
	//終了時間が有効の場合、その時間以上になったら停止する
	void Run();

	//現在の経過時間を返す
	const float& GetNowCntTime() const;

	//残り時間(終了時間-経過時間)を返す
	float GetRemainingTime() const;

	//終了時間を返す
	const float& GetEndTime() const;

	//経過時間が終了時間まで到達していたらtrueを返す
	const bool& IsTimeEnd() const;
};