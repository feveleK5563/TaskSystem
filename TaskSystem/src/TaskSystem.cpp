#include "TaskSystem.h"
#include <algorithm>

TaskSystem::TaskSystem() {}

TaskSystem::~TaskSystem()
{
	AllDeleteTask();
}

//更新
void TaskSystem::Update()
{
	AllUpdate();		//全てのタスクのUpdateを呼ぶ
	AddTask();			//追加予定のタスクを追加する
	StateDeleteTask();	//状態がDeleteのタスクを削除する
	SortTask();			//priorityを基に昇順にソートする
}

//描画
void TaskSystem::Draw()
{
	for (auto& it : task)
	{
		if (it->state != TaskState::Kill)
			it->Draw();
	}
}

//タスクを追加する
void TaskSystem::RegistrationTask(std::shared_ptr<TaskAbstract> createObj)
{
	if (createObj != nullptr)
	{
		addTask.emplace_back(createObj);
		taskData[addTask.back()->groupName].emplace_back(createObj);
	}
}

//インスタンスを得る
TaskSystem& TaskSystem::GetInstance()
{
	static TaskSystem ts;
	return ts;
}

//指定したグループ名のタスクの状態をKillにする
void TaskSystem::KillTask(const std::string& groupName)
{
	for (auto it : taskData[groupName])
	{
		it->state = TaskState::Kill;
	}
}

//登録されているタスクの状態を全てKillにする
void TaskSystem::AllKillTask()
{
	for (auto map : taskData)
	{
		for (auto it : map.second)
		{
			it->state = TaskState::Kill;
		}
	}
}

//登録済、登録予定のタスクを全て強制削除する(デストラクタで呼ばれる)
void TaskSystem::AllDeleteTask()
{
	task.clear();
	task.emplace_back();

	addTask.clear();
	addTask.emplace_back();

	taskData.clear();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//全てのタスクのUpdateを呼ぶ
void TaskSystem::AllUpdate()
{
	for (auto& it : task)
	{
		switch (it->state)
		{
		case TaskState::Active:	//状態が通常の場合は普通に更新
			it->Update();
			break;

		case TaskState::Kill:	//状態が削除要請中の場合は終了処理を呼ぶ
			it->Finalize();
			it->state = TaskState::Delete;
			break;
		}
	}
}

//追加予定のタスクを追加する
void TaskSystem::AddTask()
{
	if (addTask.empty())
		return;

	task.insert(task.end(), addTask.begin(), addTask.end());
	addTask.clear();
	addTask.shrink_to_fit();
}

//状態がDeleteのタスクを削除する
void TaskSystem::StateDeleteTask()
{
	auto deleteCondition =		//削除する条件式(状態がDelete)
		[](std::shared_ptr<TaskAbstract>& obj)
	{
		return (obj->state == TaskState::Delete);
	};

	{//オブジェクトの削除
		const auto& removeIt = std::remove_if(task.begin(), task.end(), deleteCondition);
		task.erase(removeIt, task.end());
		task.shrink_to_fit();
	}

	//データの削除
	for (auto it = taskData.begin();
		 it != taskData.end();)
	{
		const auto& removeIt = std::remove_if(it->second.begin(), it->second.end(), deleteCondition);
		it->second.erase(removeIt, it->second.end());
		it->second.shrink_to_fit();

		if ((int)it->second.size() == 0)
		{
			it = taskData.erase(it);
			continue;
		}
		++it;
	}
}

//priorityを基に昇順にソートする
void TaskSystem::SortTask()
{
	std::sort(task.begin(), task.end(), 
		[](std::shared_ptr<TaskAbstract>& left, std::shared_ptr<TaskAbstract>& right)
		{
			return (left->priority < right->priority);
		}
	);
}