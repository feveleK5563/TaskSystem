#include "GameSystem.h"
#include "DxLib.h"
#include "Fps.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "TaskSystem.h"
#include "Task_TestScene.h"
#include "ImageLoader.h"

GameSystem::GameSystem(){}

//-----------------------------------------------------------------------------
//����������
void GameSystem::Initialize()
{
	SetOutApplicationLogValidFlag(false);//Log.txt������Ȃ��悤�ɂ���

	if (IsFullScreenMode())
	{
		//�t���X�N���[�����[�h
		ChangeWindowMode(FALSE);
		//�t���X�N���[�����ɏc������ێ�����
		SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	}
	else
	{
		//�E�B���h�E���[�h
		ChangeWindowMode(TRUE);
		//�E�C���h�E�̃T�C�Y���蓮�ŕύX�ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
		SetWindowSizeChangeEnableFlag(FALSE, FALSE);
		//�E�B���h�E�T�C�Y(�𑜓x�ȉ��ɐݒ�)
		SetWindowSize(SYSDEF::SizeX, SYSDEF::SizeY);
	}

	//��ʉ𑜓x�ƃJ���[�r�b�g��
	SetGraphMode(SYSDEF::SizeX, SYSDEF::SizeY, 32);
	//�E�B���h�E�^�C�g����t����
	SetWindowText("DXlib");

	//�w�i�F�ݒ�
	SetBackgroundColor(0, 0, 0);
	
	//�������Ɨ���ʉ�
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
	{
		return;
	}

	ImageLoader::CreateInstance();

	InputDXL::CreateMouseInstance();
	InputDXL::CreateKeyInstance();
	InputDXL::CreatePadInstance(1);

	FirstCreateTask();
}

//-----------------------------------------------------------------------------
//���C�����[�v
void GameSystem::MainLoop()
{
	Fps fps;
	auto& ts = TaskSystem::GetInstance();

	while (Run())
	{
		fps.Wait();
		fps.Update();

		//�^�X�N�����݂��Ȃ������ꍇ�I������
		if (!ts.Update())
		{
			break;
		}

		ts.Draw();
		fps.Draw();
	}
}

//-----------------------------------------------------------------------------
//�I������
void GameSystem::Finalize()
{
	TaskSystem::DeleteInstance();
	ImageLoader::DeleteInstance();
	InputDXL::DeleteAllInstance();
	DxLib_End();
}

//-----------------------------------------------------------------------------
//�t���X�N���[�����[�h�ɂ��邩�ۂ������b�Z�[�W�{�b�N�X�Ŗ₤
bool GameSystem::IsFullScreenMode()
{
	int flag;
	flag = MessageBox(
				NULL,
				TEXT("�t���X�N���[�����[�h�ŋN�����܂����H"),
				TEXT("�X�N���[���ݒ�"),
				MB_YESNO | MB_ICONQUESTION);

	if (flag == IDYES)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//���[�v���񂷍ۂ̔��菈��
bool GameSystem::Run()
{
	return	ScreenFlip() == 0								//����ʂ�\��ʂɔ��f
		&&	ProcessMessage() == 0							//���b�Z�[�W����
		&&	ClearDrawScreen() == 0							//��ʂ��N���A
		&&	InputDXL::GetAllInputState()					//���͏����擾
		&&	InputDXL::GetKey()[KEY_INPUT_ESCAPE] == OFF;	//ESC��������Ă��Ȃ�
}

//-----------------------------------------------------------------------------
//�ŏ��ɍ쐬����^�X�N
void GameSystem::FirstCreateTask()
{
	//�^�X�N�V�X�e���𐶐�
	TaskSystem::CreateInstance();

	//������������������������������������������������������������
	//�Q�[���J�n���ɍ쐬����^�X�N���ȉ��ɋL�q
	TestScene::Task::Create();
}