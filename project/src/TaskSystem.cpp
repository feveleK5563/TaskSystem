#include <algorithm>
#include <assert.h>
#include "TaskSystem.h"
#include "UtilityFunctions.h"

TaskSystem::TaskSystem() {}

TaskSystem::~TaskSystem()
{
	AllDeleteTask();
}

//更新
bool TaskSystem::Update()
{
	//全てのタスクのUpdateを呼ぶ
	bool isHaveTask = AllUpdate();

	if (isHaveTask)
	{
		AddTask();			//追加予定のタスクを追加する
		StateDeleteTask();	//状態がDeleteのタスクを削除する
		SortTask();			//priorityを基に昇順にソートする
	}
	return isHaveTask;
}

//描画
void TaskSystem::Draw()
{
	for (auto& it : task)
	{
		if (it->GetTaskState() != TaskState::Kill)
			it->Draw();
	}
}

//タスクを追加する
void TaskSystem::AddTask(std::shared_ptr<TaskAbstract> createObj)
{
	if (createObj != nullptr)
	{
		addTask.emplace_back(createObj);
		taskData[addTask.back()->GetGroupName()][addTask.back()->GetTaskName()].emplace_back(createObj);
	}
}

TaskSystem* TaskSystem::ts = nullptr;
//インスタンスを得る
TaskSystem& TaskSystem::GetInstance()
{
	assert(ts != nullptr && "TaskSystem hasn't been created!");
	return *ts;
}

//インスタンスを生成する
void TaskSystem::CreateInstance()
{
	if (ts == nullptr)
	{
		ts = new TaskSystem();
	}
}

//インスタンスを解放する
void TaskSystem::DeleteInstance()
{
	UTIL::SafeDelete(ts);
}

//指定したグループ名のタスクが存在しているか調べる
bool TaskSystem::IsHaveGroup(const std::string& groupName)
{
	return taskData.find(groupName) != taskData.end();
}

//指定したグループ名のタスクを全て殺す
void TaskSystem::KillGroup(const std::string& groupName)
{
	if (!IsHaveGroup(groupName))
		return;

	for (auto itg : taskData[groupName])
	{
		for (auto itt : itg.second)
		{
			itt->KillMe();
		}
	}
}

//指定したグループ名のタスクの停止、再生を切り替える
void TaskSystem::SleepGroup(const std::string& groupName)
{
	if (!IsHaveGroup(groupName))
		return;

	for (auto itg : taskData[groupName])
	{
		for (auto itt : itg.second)
		{
			itt->SleepMe();
		}
	}
}

//指定したタスクが存在しているか調べる
bool TaskSystem::IsHaveTask(const std::string& groupName, const std::string& taskName)
{
	return	IsHaveGroup(groupName) &&
			taskData[groupName].find(taskName) != taskData[groupName].end();
}

//指定したタスクの状態をKillにする
void TaskSystem::KillTask(const std::string& groupName, const std::string& taskName)
{
	if (!IsHaveTask(groupName, taskName))
		return;

	for (auto it : taskData[groupName][taskName])
	{
		it->KillMe();
	}
}

//指定したタスクの停止、再生を切り替える
void TaskSystem::SleepTask(const std::string& groupName, const std::string& taskName)
{
	if (!IsHaveTask(groupName, taskName))
		return;

	for (auto it : taskData[groupName][taskName])
	{
		it->SleepMe();
	}
}

//登録されているタスクの状態を全てKillにする
void TaskSystem::AllKillTask()
{
	for (auto map : taskData)
	{
		for (auto itg : map.second)
		{
			for (auto itt : itg.second)
			{
				itt->KillMe();
			}
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
bool TaskSystem::AllUpdate()
{
	//タスクが存在しなかった場合falseを返す
	if (addTask.empty() && task.empty())
	{
		return false;
	}

	//先に登録予定タスクのUpdateを呼ぶ
	for (auto& it : addTask)
	{
		it->Update();
	}

	//登録済みタスクのUpdateを呼ぶ
	for (auto& it : task)
	{
		switch (it->GetTaskState())
		{
		case TaskState::Active:	//状態が通常の場合は普通に更新
			it->Update();
			break;

		case TaskState::Kill:	//状態が削除要請中の場合は終了処理を呼ぶ
			it->Finalize();
			it->SetTaskState(TaskState::Delete);
			break;
		}
	}

	return true;
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
	auto deleteCondition =		//削除する条件式(状態がDeleteの時に削除)
		[](std::shared_ptr<TaskAbstract>& obj)
	{
		return (obj->GetTaskState() == TaskState::Delete);
	};

	{//オブジェクトの削除
		const auto& removeIt = std::remove_if(task.begin(), task.end(), deleteCondition);
		task.erase(removeIt, task.end());
		task.shrink_to_fit();
	}

	//データの削除
	for (auto map = taskData.begin();
		map != taskData.end();)
	{
		for (auto itg = map->second.begin();
			itg != map->second.end();)
		{
			const auto& removeIt = std::remove_if(itg->second.begin(), itg->second.end(), deleteCondition);
			itg->second.erase(removeIt, itg->second.end());
			itg->second.shrink_to_fit();

			if (itg->second.empty())
			{
				itg = map->second.erase(itg);
				continue;
			}
			++itg;
		}

		if (map->second.empty())
		{
			map = taskData.erase(map);
			continue;
		}
		++map;
	}
}

//priorityを基に昇順にソートする
void TaskSystem::SortTask()
{
	std::sort(task.begin(), task.end(), 
		[](std::shared_ptr<TaskAbstract>& left, std::shared_ptr<TaskAbstract>& right)
		{
			return (left->GetPriority() < right->GetPriority());
		}
	);
}