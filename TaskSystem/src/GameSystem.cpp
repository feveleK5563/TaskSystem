#include "GameSystem.h"
#include "DxLib.h"
#include "Fps.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "TaskSystem.h"

#include "Task_Scene.h"

GameSystem::GameSystem(){}

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
		SetWindowSize(SystemDefine::windowSizeX, SystemDefine::windowSizeY);
	}

	//画面解像度とカラービット数
	SetGraphMode(SystemDefine::windowSizeX, SystemDefine::windowSizeY, 32);
	//ウィンドウタイトルを付ける
	SetWindowText("DxLib");

	//初期化と裏画面化
	if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
	{
		return;
	}

	auto it = Scene::Task::Create();
}

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

//ループを回す際の判定処理
bool GameSystem::Run()
{
	return	ScreenFlip() == 0 &&					//裏画面を表画面に反映
		ProcessMessage() == 0 &&					//メッセージ処理
		ClearDrawScreen() == 0 &&					//画面をクリア
		Input::key.GetInputStateAll() == 0 &&		//キーボード入力状態を保存
		Input::joypad1.GetInputStateAll() == 0 &&	//ゲームパッド入力状態を保存
		Input::key[KEY_INPUT_ESCAPE] == OFF;		//ESCが押されていない
}

//メインループ
void GameSystem::MainLoop()
{
	Fps fps;

	while (Run())
	{
		fps.Wait();
		fps.Update();
		TS::taskSystem.Update();

		fps.Draw();
		TS::taskSystem.Draw();
	}
	TS::taskSystem.AllDeleteTask();
}

//終了処理
void GameSystem::Finalize()
{
	DxLib_End();
}