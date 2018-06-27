#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "DataAbstract.h"

class ObjectAbstract
{
protected:
	std::shared_ptr<DataAbstract> data;

public:
	ObjectAbstract(std::shared_ptr<DataAbstract> data);
	virtual ~ObjectAbstract() {};
	
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const std::shared_ptr<DataAbstract>& GetData();
};