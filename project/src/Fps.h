#pragma once

class Fps
{
private:
    static const int sample_  = 60; // ���ς����T���v����
    static const int set_fps_ = 60; // �ݒ肵��FPS
    int start_time_;    // ����J�n����
    int count_;         // �J�E���^
    float fps_;         // fps

public:
    Fps();
    bool Update();
    void Wait();
    void Draw();
};