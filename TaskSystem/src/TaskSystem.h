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
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::shared_ptr<TaskAbstract>>>> taskData;

public:
	TaskSystem();
	~TaskSystem();

	bool Update();											//更新(タスクが存在しなかった場合falseを返す)
	void Draw();											//描画
	void AddTask(std::shared_ptr<TaskAbstract> createObj);	//タスクを追加する

	bool IsExistGroup(const std::string& groupName);	//指定したグループが存在しているか調べ、あったらtrueを返す
	void KillGroup(const std::string& groupName);		//指定したグループ名のタスクの状態をKillにする

	bool IsExistTask(const std::string& groupName, const std::string& taskName);	//指定したタスクが存在しているか調べる
	void KillTask(const std::string& groupName, const std::string& taskName);		//指定したタスクの状態をKillにする

	void AllKillTask();									//登録されているタスクの状態を全てKillにする
	void AllDeleteTask();								//登録されているタスクを全て強制削除する(デストラクタで呼ばれる)
	
	//指定したグループ名の内、先頭のみを渡す
	template<class T>
	std::shared_ptr<const T> GetTaskOne(const std::string& groupName, const std::string& taskName)
	{
		std::shared_ptr<const T> cpyTask;

		if (IsExistTask(groupName, taskName))
		{
			cpyTask = std::static_pointer_cast<const T>(taskData[groupName][taskName].front());
		}

		return cpyTask;
	}
	//指定したグループ名のタスクをまとめて渡す
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<const T>>> GetTaskGroup(const std::string& groupName, const std::string& taskName)
	{
		std::shared_ptr<std::vector<std::shared_ptr<const T>>> gd;

		if (IsExistTask(groupName, taskName))
		{
			gd = std::make_shared<std::vector<std::shared_ptr<const T>>>();

			gd->reserve(taskData[groupName][taskName].size() * sizeof(gd));

			for (auto it : taskData[groupName][taskName])
			{
				gd->emplace_back(std::static_pointer_cast<const T>(it));
			}
		}

		return gd;
	}

	//インスタンスを得る
	static TaskSystem& GetInstance();

private:
	bool AllUpdate();		//全てのタスクのUpdateを呼ぶ(タスクが存在しなかった場合falseを返す)
	void AddTask();			//追加予定のタスクを追加する
	void StateDeleteTask();	//状態がDeleteのタスクを削除する
	void SortTask();		//priorityを基に昇順にソートする
};

namespace TS
{
	static TaskSystem& taskSystem = TaskSystem::GetInstance();
}