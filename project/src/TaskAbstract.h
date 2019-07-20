#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Utility.h"

enum struct TaskState
{
    Active,     //通常
    Sleep,      //更新停止
    DeepSleep,  //更新と描画停止
    Kill,       //消滅要請
    Delete,     //消滅(普段は使わないこと)
}; 

class TaskAbstract
{
private:
    const std::string   task_name_;     //タスク名
    float               priority_;      //描画優先度
    TaskState           task_state_;    //状態

public:

    //コンストラクタ
    TaskAbstract(const std::string& task_name);

    //デストラクタ
    virtual ~TaskAbstract();

    virtual void Initialize() = 0;  //初期化処理(必須)
    virtual void Finalize() = 0;    //終了処理(必須)
    virtual void Update() {};       //更新
    virtual void Draw() {};         //描画

    void SetPriority(float set_priority);        //描画優先度を設定
    void SetTaskState(TaskState set_task_state); //タスクの状態を設定

    const std::string&  GetTaskName();  //タスク名を取得
    const float&        GetPriority();  //描画優先度を取得
    const TaskState&    GetTaskState(); //タスクの状態を取得
};