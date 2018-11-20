#include "Task_TestScene.h"
#include "ImageLoader.h"
#include "InputState.h"
#include "SystemDefine.h"

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
		imgDrawer.Initialize(ImageLoader::GetInstance().GetImageData(res->imageName), true);

		//constantBuffer�̃T�C�Y��24�����A�Ȃ�2�̗ݏ悶��Ȃ��Ɛ���Ɋm�ۂ��Ă���Ȃ����ۂ��̂�32�����m��
		pscbhandle = CreateShaderConstantBuffer(32);
		pshandle = LoadPixelShader("data/shader/circle.pso");

		float x = (float)SYSDEF::SizeX, y = (float)SYSDEF::SizeY;
		vertex[0].pos = VGet(-1.f, -1.f, 0.f);
		vertex[1].pos = VGet(x, -1.f, 0.f);
		vertex[2].pos = VGet(-1.f, y, 0.f);
		vertex[3].pos = VGet(x, y, 0.f);

		for (int i = 0; i < 4; ++i)
		{
			vertex[i].rhw = 1.f;
			vertex[i].dif = GetColorU8(255, 255, 255, 255);
			vertex[i].spc = GetColorU8(0, 0, 0, 0);
			vertex[i].u = float(i % 2);
			vertex[i].su = float(i % 2); 
			vertex[i].v = float(i / 2);
			vertex[i].sv = float(i / 2);
		}
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{
		DeleteShader(pshandle);
		DeleteShaderConstantBuffer(pscbhandle);
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
		constantBuffer* cb = (constantBuffer*)GetBufferShaderConstantBuffer(pscbhandle);

		//�e�l���擾�����A�h���X�ɏ�������
		cb->windowSize.u = (float)SYSDEF::SizeX;
		cb->windowSize.v = (float)SYSDEF::SizeY;
		cb->mousePos.u = mousePos.x;
		cb->mousePos.v = mousePos.y;
		cb->radius = timer.GetNow();
		cb->onClick = onClick;
		//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
		UpdateShaderConstantBuffer(pscbhandle);
		//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^0�ɃZ�b�g
		SetShaderConstantBuffer(pscbhandle, DX_SHADERTYPE_PIXEL, 0);

		//�s�N�Z���V�F�[�_�̃Z�b�g
		SetUsePixelShader(pshandle);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		//�`��
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);

		imgDrawer.Draw(MATH::Vec2(100, 100));
	}
}