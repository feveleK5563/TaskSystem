#pragma once

class Fps
{
private:
	static const int N = 60;	//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS
	int mStartTime;				//測定開始時刻
	int mCount;					//カウンタ
	float mFps;					//fps

public:
	Fps();
	bool Update();
	void Wait();
	void Draw();
};