#include "GameSystem.h"
#include "DxLib.h"
#include "Fps.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "TaskSystem.h"
#include "Task_TestScene.h"

GameSystem::GameSystem(){}

//-----------------------------------------------------------------------------
//初期化処理
void GameSystem::Initialize()
{
	SetOutApplicationLogValidFlag(false);//Log.txtが作られないようにする

	if (IsFullScreenMode())
	{
		//フルスクリーンモード
		ChangeWindowMode(FALSE);
		//フルスクリーン時に縦横比を維持する
		SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
	}
	else
	{
		//ウィンドウモード
		ChangeWindowMode(TRUE);
		//ウインドウのサイズを手動で変更できず、且つウインドウのサイズに合わせて拡大もしないようにする
		SetWindowSizeChangeEnableFlag(FALSE, FALSE);
		//ウィンドウサイズ(解像度以下に設定)
		SetWindowSize(DEF::SizeX, DEF::SizeY);
	}

	//画面解像度とカラービット数
	SetGraphMode(DEF::SizeX, DEF::SizeY, 32);
	//ウィンドウタイトルを付ける
	SetWindowText("DXlib");

	//初期化と裏画面化
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
	{
		return;
	}

	FirstCreateTask();
}

//-----------------------------------------------------------------------------
//メインループ
void GameSystem::MainLoop()
{
	Fps fps;

	while (Run())
	{
		fps.Wait();
		fps.Update();
		//タスクが存在しなかった場合終了する
		if (!TS::taskSystem.Update())
		{
			break;
		}

		TS::taskSystem.Draw();
		fps.Draw();
	}
}

//-----------------------------------------------------------------------------
//終了処理
void GameSystem::Finalize()
{
	DxLib_End();
}

//-----------------------------------------------------------------------------
//フルスクリーンモードにするか否かをメッセージボックスで問う
bool GameSystem::IsFullScreenMode()
{
	int flag;
	flag = MessageBox(
				NULL,
				TEXT("フルスクリーンモードで起動しますか？"),
				TEXT("スクリーン設定"),
				MB_YESNO | MB_ICONQUESTION);

	if (flag == IDYES)
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//ループを回す際の判定処理
bool GameSystem::Run()
{
	return	ScreenFlip() == 0 &&					//裏画面を表画面に反映
		ProcessMessage() == 0 &&					//メッセージ処理
		ClearDrawScreen() == 0 &&					//画面をクリア
		INP::GetInputStateAll() &&				//入力情報を取得
		INP::key[KEY_INPUT_ESCAPE] == OFF;		//ESCが押されていない
}

//-----------------------------------------------------------------------------
//最初に作成するタスク
void GameSystem::FirstCreateTask()
{
	//最初に作成するタスクをここに入力
	TestScene::Task::Create();
}