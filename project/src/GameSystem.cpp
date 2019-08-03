#include "GameSystem.h"
#include "DxLib.h"
#include "Fps.h"
#include "SystemDefine.h"
#include "InputDXL.h"
#include "PadInputConfig.h"
#include "TaskSystem.h"
#include "ImageLoader.h"
#include "ShaderManager.h"
#include "Utility.h"

#include "Task_Test.h"

GameSystem::GameSystem(){}

//-----------------------------------------------------------------------------
// ����������
void GameSystem::Initialize()
{
    SetAlwaysRunFlag(TRUE); // �E�B���h�E���m���A�N�e�B�u�ł����s����
    SetOutApplicationLogValidFlag(FALSE); // Log.txt�����Ȃ�

    if (IsFullScreenMode())
    {
        // �t���X�N���[�����[�h
        ChangeWindowMode(FALSE);
        // �t���X�N���[�����ɏc������ێ�����
        SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
    }
    else
    {
        // �E�B���h�E���[�h
        ChangeWindowMode(TRUE);
        // �E�C���h�E�̃T�C�Y���蓮�ŕύX�ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);
        // �E�B���h�E�T�C�Y(�𑜓x�ȉ��ɐݒ�)
        SetWindowSize(SysDef::SizeX, SysDef::SizeY);
    }

    // ��ʉ𑜓x�ƃJ���[�r�b�g��
    SetGraphMode(SysDef::SizeX, SysDef::SizeY, 32);
    // �E�B���h�E�^�C�g����t����
    SetWindowText("DXlib");

    // �w�i�F�ݒ�
    SetBackgroundColor(0, 0, 0);

    // �������Ɨ���ʉ�
    if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
    {
        return;
    }

    ImageLoader::Create();
    ShaderManager::Create();

    InputDXL::CreateMouseInstance();    // �}�E�X�𐶐�
    InputDXL::CreateKeyInstance();      // �L�[�{�[�h�𐶐�
    InputDXL::CreatePadInstance(SysDef::PadNum);        // �Q�[���p�b�h���w�������
    PadInputConfig::Create(SysDef::PadNum, true, true); // �Q�[���p�b�h�̃R���t�B�O���쐬����

    FirstCreateTask();
}

//-----------------------------------------------------------------------------
// ���C�����[�v
void GameSystem::MainLoop()
{
    Fps fps;

    while (Run())
    {
        fps.Wait();
        fps.Update();

        // �^�X�N�����݂��Ȃ������ꍇ�I������
        if (TaskSystem::GetAllTaskNum() == 0)
        {
            DOUT << "[System End]" << std::endl;
            break;
        }
        TaskSystem::Update();

        TaskSystem::Draw();
        //fps.Draw();
    }
}

//-----------------------------------------------------------------------------
// �I������
void GameSystem::Finalize()
{
    TaskSystem::Delete();
    ImageLoader::Delete();
    ShaderManager::Delete();
    InputDXL::DeleteAllInstance();
    PadInputConfig::Delete();
    DxLib_End();
}

//-----------------------------------------------------------------------------
// �t���X�N���[�����[�h�ɂ��邩�ۂ������b�Z�[�W�{�b�N�X�Ŗ₤
bool GameSystem::IsFullScreenMode()
{
    int flag;
    flag = MessageBox(
                NULL,
                TEXT("�t���X�N���[�����[�h�ŋN�����܂����H"),
                TEXT("�X�N���[���ݒ�"),
                MB_YESNO | MB_ICONQUESTION);

    if (flag == IDYES) { return true; }
    return false;
}

//-----------------------------------------------------------------------------
// ���[�v���񂷍ۂ̔��菈��
bool GameSystem::Run()
{
    return  ScreenFlip() == 0                               // ����ʂ�\��ʂɔ��f
        &&  ProcessMessage() == 0                           // ���b�Z�[�W����
        &&  ClearDrawScreen() == 0                          // ��ʂ��N���A
        &&  InputDXL::GetAllInputState()                    // ���͏����擾
        &&  InputDXL::GetKey()[KEY_INPUT::ESCAPE] == OFF;   // ESC��������Ă��Ȃ�
}

//-----------------------------------------------------------------------------
// �ŏ��ɍ쐬����^�X�N
void GameSystem::FirstCreateTask()
{
    // �^�X�N�V�X�e���𐶐�
    TaskSystem::Create();

    //������������������������������������������������������������
    // �Q�[���J�n���ɍ쐬����^�X�N���ȉ��ɋL�q ���x���ł邩��(void)�t���Ă�
    (void)Test::Task::Create();
}