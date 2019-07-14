#include "Fps.h"
#include <math.h>
#include "DxLib.h"

Fps::Fps():
    start_time_(0),
    count_(0),
    fps_(0) {}

bool Fps::Update()
{
    if (count_ == 0)    //1�t���[���ڂȂ玞�����L��
    {
        start_time_ = GetNowCount();
    }

    if (count_ == sample_)  //60�t���[���ڂȂ畽�ς��v�Z����
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
    int tookTime = GetNowCount() - start_time_;     //������������
    int waitTime = count_ * 1000 / set_fps_ - tookTime; //�҂ׂ�����
    if (waitTime > 0)
    {
        Sleep(waitTime);    //�ҋ@
    }
}

void Fps::Draw()
{
    DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", fps_);
}