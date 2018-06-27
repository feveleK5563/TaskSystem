#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include "ObjectAbstract.h"

class TaskSystem
{
private:
	std::vector<std::shared_ptr<ObjectAbstract>> object;
	std::vector<std::shared_ptr<ObjectAbstract>> addObject;
	std::unordered_map<std::string, std::vector<std::shared_ptr<DataAbstract>>> objData;

public:
	TaskSystem() {};

	void Update();
	void Draw();
	void CreateObject(std::shared_ptr<ObjectAbstract> createObj);
	
	template<class T>
	std::shared_ptr<const T> GetDataOne(const std::string& groupName)
	{
		if (objData.find(groupName) != objData.end())
		{
			return std::static_pointer_cast<const T>(objData[groupName][0]);
		}

		return nullptr;
	}

	template<class T>
	std::shared_ptr<std::vector<std::shared_ptr<const T>>> GetDataGroup(const std::string& groupName)
	{
		if (objData.find(groupName) != objData.end())
		{
			std::shared_ptr<std::vector<std::shared_ptr<const T>>> gd =
				std::make_shared<std::vector<std::shared_ptr<const T>>>();

			for (auto it : objData[groupName])
			{
				gd->emplace_back(std::static_pointer_cast<const T>(it));
			}

			return gd;
		}

		return nullptr;
	}

	static TaskSystem& GetInstance();

private:
	void AllUpdate();
	void AddObject();
	void KillObject();
	void SortObject();
};

namespace TS
{
	static TaskSystem& taskSystem = TaskSystem::GetInstance();
}