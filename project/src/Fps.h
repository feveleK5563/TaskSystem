#pragma once

class Fps
{
private:
    static const int sample_  = 60; // 平均を取るサンプル数
    static const int set_fps_ = 60; // 設定したFPS
    int start_time_;    // 測定開始時刻
    int count_;         // カウンタ
    float fps_;         // fps

public:
    Fps();
    bool Update();
    void Wait();
    void Draw();
};