#include "Task_TestScene.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "InputState.h"

namespace TestScene
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		IMG::imageLoader.LoadDivImage("Bomb", "data/image/bomb.png", 12, 12, 1, 64, 64);
		IMG::imageLoader.AddAnimationData("Bomb", 0, 11, 5.f, true);
		imgData = IMG::imageLoader.GetImageData("Bomb");
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		
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
		plus(0, 0)
	{
		imgDrawer.Initialize(res->imgData, true);
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
		TS::taskSystem.AddTask(task);

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
		//imgDrawer.AnimUpdate();

		auto& pad = InputDXL::GetPad(0);
		if (pad[PadButton::A] == DOWN)
		{
			TS::taskSystem.AllKillTask();
		}

		float vol = pad.GetVolumeStickL() * 100.f;
		float ang = pad.GetAngleStickL();
		plus = MATH::Vec2(cos(ang) * vol, sin(ang) * vol);
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		imgDrawer.DrawOne(MATH::Vec2(300, 300) + plus,
			1.f,
			1.f,
			false,
			5,
			Color(255, 255, 255, 255));
	}
}