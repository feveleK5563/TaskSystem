#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "TaskAbstract.h"

class TaskSystem
{
private:
	std::vector<std::shared_ptr<TaskAbstract>> task;
	std::vector<std::shared_ptr<TaskAbstract>> addTask;
	std::unordered_map<std::string, std::vector<std::shared_ptr<TaskAbstract>>> taskData;

public:
	TaskSystem();
	~TaskSystem();

	void Update();													//更新
	void Draw();													//描画
	void RegistrationTask(std::shared_ptr<TaskAbstract> createObj);	//タスクを追加する

	void KillTask(const std::string& groupName);	//指定したグループ名のタスクの状態をKillにする
	void AllKillTask();								//登録されているタスクの状態を全てKillにする
	void AllDeleteTask();							//登録されているタスクを全て強制削除する(デストラクタで呼ばれる)
	
	//指定したグループ名の内、先頭のみを渡す
	template<class T>
	std::shared_ptr<const T> GetTaskOne(const std::string& groupName)
	{
		if (taskData.find(groupName) != taskData.end())
		{
			return std::static_pointer_cast<const T>(taskData[groupName].front());
		}

		return nullptr;
	}

	//指定したグループ名のタスクをまとめて渡す
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<const T>>> GetTaskGroup(const std::string& groupName)
	{
		if (taskData.find(groupName) != taskData.end())
		{
			std::shared_ptr<std::vector<std::shared_ptr<const T>>> gd =
				std::make_shared<std::vector<std::shared_ptr<const T>>>();

			gd->reserve(taskData[groupName].size() * sizeof(gd));

			for (auto it : taskData[groupName])
			{
				gd->emplace_back(std::static_pointer_cast<const T>(it));
			}

			return gd;
		}

		return nullptr;
	}

	//インスタンスを得る
	static TaskSystem& GetInstance();

private:
	void AllUpdate();		//全てのタスクのUpdateを呼ぶ
	void AddTask();			//追加予定のタスクを追加する
	void StateDeleteTask();	//状態がDeleteのタスクを削除する
	void SortTask();		//priorityを基に昇順にソートする
};

namespace TS
{
	static TaskSystem& taskSystem = TaskSystem::GetInstance();
}