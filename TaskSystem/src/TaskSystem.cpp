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
	for (auto& it : object)
	{
		it->Draw();
	}
}

void TaskSystem::CreateObject(std::shared_ptr<ObjectAbstract> createObj)
{
	if (createObj != nullptr)
	{
		addObject.emplace_back(createObj);
		auto data = addObject.back()->GetData();
		objData[data->groupName].emplace_back(data);
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
	for (auto& it : object)
	{
		it->Update();
	}
}

//追加予定のオブジェクトを追加する
void TaskSystem::AddObject()
{
	if (addObject.empty())
		return;

	object.insert(object.end(), addObject.begin(), addObject.end());
	addObject.clear();
	addObject.shrink_to_fit();
}

//状態がKillのオブジェクトを削除する
void TaskSystem::KillObject()
{
	{//オブジェクトの削除
		const auto& removeIt = std::remove_if(object.begin(), object.end(),
			[](std::shared_ptr<ObjectAbstract>& obj)
		{
			return (obj->GetData()->state == ObjectState::Kill);
		}
		);
		object.erase(removeIt, object.end());
		object.shrink_to_fit();
	}

	//データの削除
	for (auto it = objData.begin();
		 it != objData.end();
		 ++it)
	{
		const auto& removeIt = std::remove_if(it->second.begin(), it->second.end(),
			[](std::shared_ptr<DataAbstract>& data)
		{
			return (data->state == ObjectState::Kill);
		}
		);
		it->second.erase(removeIt, it->second.end());
		it->second.shrink_to_fit();

		if ((int)it->second.size() == 0)
		{
			objData.erase(it);
		}
	}
}

//priorityを基に昇順にソートする
void TaskSystem::SortObject()
{
	std::sort(object.begin(), object.end(), 
		[](std::shared_ptr<ObjectAbstract>& left, std::shared_ptr<ObjectAbstract>& right)
		{
			return (left->GetData()->priority < right->GetData()->priority);
		}
	);
}