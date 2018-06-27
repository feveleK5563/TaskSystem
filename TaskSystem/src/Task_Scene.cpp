#include "Task_Scene.h"
#include "DxLib.h"

Task_Scene::Task_Scene():
	ObjectAbstract(std::make_shared<Data_Scene>("‚ ‚¢‚¤‚¦‚¨", 0.1f))
{

}

void Task_Scene::Update()
{
	auto me = TS::taskSystem.GetDataGroup<Data_Scene>("‚ ‚¢‚¤‚¦‚¨");
	(*me)[0]->hogehoge;
}

void Task_Scene::Draw()
{
	DrawString(100, 100, "hogehoge", GetColor(255, 255, 255));
}

//-----------------------------------------------------------------------------
const std::shared_ptr<const Task_Scene> Task_Scene::Create()
{
	std::shared_ptr<Task_Scene> task = std::make_shared<Task_Scene>();
	TS::taskSystem.CreateObject(task);

	return task;
}