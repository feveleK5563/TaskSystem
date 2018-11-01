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

	TaskSystem();
	static TaskSystem* ts;

public:
	~TaskSystem();

	bool Update();											//更新(タスクが存在しなかった場合falseを返す)
	void Draw();											//描画
	void AddTask(std::shared_ptr<TaskAbstract> createObj);	//タスクを追加する

	bool IsHaveGroup(const std::string& groupName);	//指定したグループが存在しているか調べる
	void KillGroup(const std::string& groupName);		//指定したグループ名のタスクを全て殺す
	void SleepGroup(const std::string& groupName);		//指定したグループ名のタスクの停止、再生を切り替える

	bool IsHaveTask(const std::string& groupName, const std::string& taskName);	//指定したタスクが存在しているか調べる
	void KillTask(const std::string& groupName, const std::string& taskName);		//指定したタスクを全て殺す
	void SleepTask(const std::string& groupName, const std::string& taskName);		//指定したタスクの停止、再生を切り替える

	void AllKillTask();		//登録されているタスクを全て殺す
	void AllDeleteTask();	//登録されているタスクを全て強制削除する(デストラクタで呼ばれる)
	
	//指定したタスクの内、先頭のみを渡す
	template<class T>
	std::shared_ptr<T> GetTaskOne(const std::string& groupName, const std::string& taskName)
	{
		if (IsHaveTask(groupName, taskName))
		{
			return std::static_pointer_cast<T>(taskData[groupName][taskName].front());
		}

		return std::shared_ptr<T>();
	}
	//指定したタスクをまとめて渡す
	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<T>>> GetTaskGroup(const std::string& groupName, const std::string& taskName)
	{
		std::shared_ptr<std::vector<std::shared_ptr<T>>> gt;

		if (IsHaveTask(groupName, taskName))
		{
			gt = std::make_shared<std::vector<std::shared_ptr<T>>>();

			gt->reserve(taskData[groupName][taskName].size());

			for (auto it : taskData[groupName][taskName])
			{
				gt->emplace_back(std::static_pointer_cast<T>(it));
			}
		}

		return gt;
	}

	//インスタンスを得る
	static TaskSystem& GetInstance();
	//インスタンスを生成する
	static void CreateInstance();
	//インスタンスを解放する
	static void DeleteInstance();

private:
	bool AllUpdate();		//全てのタスクのUpdateを呼ぶ(タスクが存在しなかった場合falseを返す)
	void AddTask();			//追加予定のタスクを追加する
	void StateDeleteTask();	//状態がDeleteのタスクを削除する
	void SortTask();		//priorityを基に昇順にソートする
};