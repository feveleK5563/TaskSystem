#pragma once
#include "TaskSystem.h"
#include "Data_Scene.h"

class Task_Scene : public ObjectAbstract
{
public:
	Task_Scene();

	void Update() override;
	void Draw() override;

	static const std::shared_ptr<const Task_Scene> Create();
};