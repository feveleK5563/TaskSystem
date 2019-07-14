#include "Fps.h"
#include <math.h>
#include "DxLib.h"

Fps::Fps():
    start_time_(0),
    count_(0),
    fps_(0) {}

bool Fps::Update()
{
    if (count_ == 0)    //1フレーム目なら時刻を記憶
    {
        start_time_ = GetNowCount();
    }

    if (count_ == sample_)  //60フレーム目なら平均を計算する
    {
        int t = GetNowCount();
        fps_ = 1000.f / ((t - start_time_) / (float)sample_);
        count_ = 0;
        start_time_ = t;
    }
    ++count_;
    return true;
}

void Fps::Wait()
{
    int tookTime = GetNowCount() - start_time_;     //かかった時間
    int waitTime = count_ * 1000 / set_fps_ - tookTime; //待つべき時間
    if (waitTime > 0)
    {
        Sleep(waitTime);    //待機
    }
}

void Fps::Draw()
{
    DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", fps_);
}