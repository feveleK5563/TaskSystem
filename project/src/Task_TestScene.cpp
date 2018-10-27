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
		auto& imageLoader = ImageLoader::GetInstance();
		imageName = "Bomb";
		imageLoader.LoadDivImage(imageName, "data/image/bomb.png", 12, 12, 1, 64, 64);
		imageLoader.AddAnimationData(imageName, 0, 11, 5.f, true);
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		auto& imageLoader = ImageLoader::GetInstance();
		imageLoader.DeleteImageData(imageName);
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
		imgDrawer.Initialize(
			ImageLoader::GetInstance().GetImageData(res->imageName), true);
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
		
		auto& pad = InputDXL::GetPad(0);
		auto& mouse = InputDXL::GetMouse();
		if (mouse[MouseButton::RIGHT] == DOWN)
		{
			TaskSystem::GetInstance().AllKillTask();
		}

		float vol = pad.GetVolumeStickR() * 200.f;
		float ang = pad.GetAngleStickR();
		plus = MATH::Vec2(cos(ang) * vol, sin(ang) * vol);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%.1f", MATH::ToDegree(ang));
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		/*imgDrawer.Draw(MATH::Vec2(0, 0) + plus,
			1.f,
			1.f,
			0.f,
			false,
			Color(255, 255, 255, 255));*/

		//imgDrawer.Draw(MATH::Vec2(0, 0) + plus);

		imgDrawer.DrawOne(
			7,
			plus + MATH::Vec2(300.f, 300.f),
			MATH::Vec2(16, 16),
			MATH::Box2D(16, 16, 32, 32),
			false);
	}
}