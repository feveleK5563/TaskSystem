#pragma once

class Fps
{
private:
	static const int N = 60;	//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS
	int mStartTime;				//����J�n����
	int mCount;					//�J�E���^
	float mFps;					//fps

public:
	Fps();
	bool Update();
	void Wait();
	void Draw();
};