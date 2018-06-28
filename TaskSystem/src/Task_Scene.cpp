#include "Task_Scene.h"
#include "DxLib.h"

namespace Scene
{
	Task::Task() :
		TaskAbstract(gn, 0.f),
		hogehoge(0)
	{

	}

	void Task::Update()
	{
		auto me = TS::taskSystem.GetTaskGroup<Scene::Task>("‚ ‚¢‚¤‚¦‚¨");
		(*me)[0]->hogehoge;
	}

	void Task::Draw()
	{
		DrawString(100, 100, "hogehoge", GetColor(255, 255, 255));
	}

	//-----------------------------------------------------------------------------
	const std::shared_ptr<const Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationObject(task);

		return task;
	}
}