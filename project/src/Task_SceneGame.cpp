#include "Task_SceneGame.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"
#include "ShaderManager.h"

namespace SceneGame
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
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
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);

		auto& shaderManager = ShaderManager::GetInstance();
		shaderManager.DeleteShaderData(sName);
		shaderManager.DeleteConstantBuffer(cbName);
	}
	//----------------------------------------------
	//���\�[�X�̐���
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

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defTaskName, defPriority),
		res(Resource::Create()),
		timer(40.f),
		mousePos(0, 0),
		onClick(false)
	{

	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
		TaskSystem::GetInstance().AddTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		//�摜�󂯎��
		imgDrawer.Initialize(ImageLoader::GetInstance().GetImageData(res->imageName), Math::BoxCP::MIDDLE_MIDDLE);
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
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
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
		auto& shaderManager = ShaderManager::GetInstance();
		auto& cb = shaderManager.GetConstantBuffer<constantBuffer>(res->cbName);

		//�e�l����������
		cb.windowSize.u = (float)SysDef::SizeX;
		cb.windowSize.v = (float)SysDef::SizeY;
		cb.mousePos.u = mousePos.x;
		cb.mousePos.v = mousePos.y;
		cb.radius = timer.GetNow();
		cb.onClick = onClick;

		//�`��
		imgDrawer.Draw(Math::Vec2(100, 100));

		//shaderManager.DrawShader(res->sName, res->cbName);
	}
}