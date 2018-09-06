#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>

enum struct TaskState
{
	Ready,		//準備
	Active,		//通常
	Sleep,		//停止
	Kill,		//消滅要請
	Delete,		//消滅
}; 

class TaskAbstract
{
private:
	const std::string	groupName;	//グループ名
	const std::string	taskName;	//タスク名
	float				priority;	//描画優先度
	TaskState			taskState;	//状態

public:

	//コンストラクタ
	TaskAbstract(	const std::string& groupName,
					const std::string& taskName,
					float priority,
					TaskState state = TaskState::Active);

	//デストラクタ
	virtual ~TaskAbstract() {};
	
	virtual void Initialize() = 0;	//初期化処理
	virtual void Finalize() = 0;	//終了処理
	virtual void Update() = 0;		//更新
	virtual void Draw() = 0;		//描画

	void KillMe();	//自分を殺す
	void SleepMe();	//自分を停止状態にする

	void SetPriority(float setPriority);		//描画優先度を設定
	void SetTaskState(TaskState setTaskState);	//タスクの状態を設定

	const std::string&	GetGroupName();	//タスクのグループ名を取得
	const std::string&	GetTaskName();	//タスク名を取得
	const float&		GetPriority();	//描画優先度を取得
	const TaskState&	GetTaskState();	//タスクの状態を取得
};