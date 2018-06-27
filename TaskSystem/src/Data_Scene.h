#pragma once
#include "DataAbstract.h"

struct Data_Scene : public DataAbstract
{
	int hogehoge;

	Data_Scene(const std::string& groupName, float priority) :
		DataAbstract(groupName, priority),
		hogehoge(180){}
};