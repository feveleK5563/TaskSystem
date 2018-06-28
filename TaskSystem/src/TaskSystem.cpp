#include "TaskSystem.h"
#include <algorithm>

void TaskSystem::Update()
{
	AllUpdate();	//全てのオブジェクトのUpdateを呼ぶ
	AddObject();	//追加予定のオブジェクトを追加する
	KillObject();	//状態がKillのオブジェクトを削除する

	SortObject();	//priorityを基に昇順にソートする
}

void TaskSystem::Draw()
{
	for (auto& it : task)
	{
		it->Draw();
	}
}

void TaskSystem::RegistrationObject(std::shared_ptr<TaskAbstract> createObj)
{
	if (createObj != nullptr)
	{
		addTask.emplace_back(createObj);
		taskData[addTask.back()->groupName].emplace_back(createObj);
	}
}

TaskSystem& TaskSystem::GetInstance()
{
	static TaskSystem ts;
	return ts;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//全てのオブジェクトのUpdateを呼ぶ
void TaskSystem::AllUpdate()
{
	for (auto& it : task)
	{
		it->Update();
	}
}

//追加予定のオブジェクトを追加する
void TaskSystem::AddObject()
{
	if (addTask.empty())
		return;

	task.insert(task.end(), addTask.begin(), addTask.end());
	addTask.clear();
	addTask.shrink_to_fit();
}

//状態がKillのオブジェクトを削除する
void TaskSystem::KillObject()
{
	{//オブジェクトの削除
		const auto& removeIt = std::remove_if(task.begin(), task.end(),
			[](std::shared_ptr<TaskAbstract>& obj)
		{
			return (obj->state == ObjectState::Kill);
		}
		);
		task.erase(removeIt, task.end());
		task.shrink_to_fit();
	}

	//データの削除
	for (auto it = taskData.begin();
		 it != taskData.end();
		 ++it)
	{
		const auto& removeIt = std::remove_if(it->second.begin(), it->second.end(),
			[](std::shared_ptr<TaskAbstract>& data)
		{
			return (data->state == ObjectState::Kill);
		}
		);
		it->second.erase(removeIt, it->second.end());
		it->second.shrink_to_fit();

		if ((int)it->second.size() == 0)
		{
			taskData.erase(it);
		}
	}
}

//priorityを基に昇順にソートする
void TaskSystem::SortObject()
{
	std::sort(task.begin(), task.end(), 
		[](std::shared_ptr<TaskAbstract>& left, std::shared_ptr<TaskAbstract>& right)
		{
			return (left->priority < right->priority);
		}
	);
}