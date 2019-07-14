#include "Task_SceneGame.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"
#include "ShaderManager.h"

namespace SceneGame
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

		auto& shaderManager = ShaderManager::GetInstance();
		sName = "shader";
		bool hoge = shaderManager.LoadShader(sName, "data/shader/circle.pso");
		cbName = "constantBuffer";
		hoge = shaderManager.CreateConstantBuffer<constantBuffer>(cbName);
	}
	//----------------------------------------------
	//リソースのデストラクタ
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);

		auto& shaderManager = ShaderManager::GetInstance();
		shaderManager.DeleteShaderData(sName);
		shaderManager.DeleteConstantBuffer(cbName);
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
		timer(40.f),
		mousePos(0, 0),
		onClick(false)
	{

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
		//画像受け取り
		imgDrawer.Initialize(ImageLoader::GetInstance().GetImageData(res->imageName), Math::BoxCP::MIDDLE_MIDDLE);
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
		imgDrawer.AnimUpdate();
		timer.Run();

		auto& mouse = InputDXL::GetMouse();
		if (mouse[MouseButton::LEFT] == DOWN)
		{
			mousePos = mouse.GetPos();
			onClick = !onClick;
			timer.Reset();
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{
		//ピクセルシェーダー用の定数バッファのアドレスを取得
		auto& shaderManager = ShaderManager::GetInstance();
		auto& cb = shaderManager.GetConstantBuffer<constantBuffer>(res->cbName);

		//各値を書き込み
		cb.windowSize.u = (float)SysDef::SizeX;
		cb.windowSize.v = (float)SysDef::SizeY;
		cb.mousePos.u = mousePos.x;
		cb.mousePos.v = mousePos.y;
		cb.radius = timer.GetNow();
		cb.onClick = onClick;

		//描画
		imgDrawer.Draw(Math::Vec2(100, 100));

		//shaderManager.DrawShader(res->sName, res->cbName);
	}
}