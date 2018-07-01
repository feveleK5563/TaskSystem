#include "Task_Scene.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "SystemDefine.h"

namespace Scene
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		Image::imageLoader.LoadDivImage("Bomb", "data/image/bomb.png", 12, 12, 1, 64, 64);
		Image::imageLoader.AddAnimationData("Bomb", 0, 11, 1.f, false);
		//imgData = Image::imageLoader.GetImageData("Bomb");
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		Image::imageLoader.DeleteImageData("Bomb");
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
		TaskAbstract(defGroupName, defPriority),
		res(Resource::Create())/*,
		imgDrawer(res->imgData, {0, 0})*/
	{ 
		Initialize();
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	const std::shared_ptr<const Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

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
		//imgDrawer.Run();
		int uc = res.use_count();
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		//DrawString(100, 100, "hogehoge", GetColor(255, 255, 255));
		/*imgDrawer.Draw(	Math::Vec2(100, 100),
						1.f,
						0.f,
						false,
						Color(255, 255, 255, 255));*/
	}
}