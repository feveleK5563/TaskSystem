#include "Task_TestScene.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "InputState.h"

namespace TestScene
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//リソースのコンストラクタ
	Resource::Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageName = "Bomb";
		imageLoader.LoadDivImage(imageName, "data/image/bomb.png", 12, 12, 1, 64, 64);
		imageLoader.AddAnimationData(imageName, 0, 11, 5.f, true);
	}
	//----------------------------------------------
	//リソースのデストラクタ
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);
	}
	//----------------------------------------------
	//リソースの生成
	std::shared_ptr<Resource> Resource::Create()
	{
		auto sp = instance.lock();
		if (!sp)
		{
			sp = std::make_shared<Resource>();
			instance = sp;
		}
		return sp;
	}

	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create()),
		plus(0, 0),
		hoge(1, 0, 100)
	{
		imgDrawer.Initialize(
			ImageLoader::GetInstance().GetImageData(res->imageName), true);
	}
	//----------------------------------------------
	//タスクのデストラクタ
	Task::~Task()
	{

	}
	//----------------------------------------------
	//タスクの生成
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TaskSystem::GetInstance().AddTask(task);

		task->Initialize();
		return task;
	}

	//◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
	//◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

	//----------------------------------------------
	//初期化処理
	//----------------------------------------------
	void Task::Initialize()
	{

	}

	//----------------------------------------------
	//終了処理
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//更新
	//----------------------------------------------
	void Task::Update()
	{
		hoge.RunLoop();
		imgDrawer.AnimUpdate();
		
		auto& mouse = InputDXL::GetMouse();
		if (mouse[MouseButton::RIGHT] == DOWN)
		{
			TaskSystem::GetInstance().AllKillTask();
		}

		auto& task = TaskSystem::GetInstance();
		if (task.GetTaskGroup<TestScene::Task>(defGroupName, defTaskName))
		{
			DrawFormatString(0, 25, GetColor(255, 255, 255), "(^^) < You are an idiot.");
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		/*imgDrawer.Draw(MATH::Vec2(0, 0) + plus,
			1.f,
			1.f,
			0.f,
			false,
			Color(255, 255, 255, 255));*/

		imgDrawer.Draw(MATH::Vec2(300, 300) + plus);
		DrawFormatString(0, 50, GetColor(255, 255, 255), "%d", hoge.GetNow());

		/*imgDrawer.DrawOne(
			7,
			plus + MATH::Vec2(300.f, 300.f),
			MATH::Vec2(16, 16),
			MATH::Box2D(16, 16, 32, 32),
			false);*/
	}
}