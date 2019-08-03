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
// 初期化処理
void GameSystem::Initialize()
{
    SetAlwaysRunFlag(TRUE); // ウィンドウがノンアクティブでも実行する
    SetOutApplicationLogValidFlag(FALSE); // Log.txtを作らない

    if (IsFullScreenMode())
    {
        // フルスクリーンモード
        ChangeWindowMode(FALSE);
        // フルスクリーン時に縦横比を維持する
        SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);
    }
    else
    {
        // ウィンドウモード
        ChangeWindowMode(TRUE);
        // ウインドウのサイズを手動で変更できず、且つウインドウのサイズに合わせて拡大もしないようにする
        SetWindowSizeChangeEnableFlag(FALSE, FALSE);
        // ウィンドウサイズ(解像度以下に設定)
        SetWindowSize(SysDef::SizeX, SysDef::SizeY);
    }

    // 画面解像度とカラービット数
    SetGraphMode(SysDef::SizeX, SysDef::SizeY, 32);
    // ウィンドウタイトルを付ける
    SetWindowText("DXlib");

    // 背景色設定
    SetBackgroundColor(0, 0, 0);

    // 初期化と裏画面化
    if (DxLib_Init() == -1 || SetDrawScreen(DX_SCREEN_BACK) != 0)
    {
        return;
    }

    ImageLoader::Create();
    ShaderManager::Create();

    InputDXL::CreateMouseInstance();    // マウスを生成
    InputDXL::CreateKeyInstance();      // キーボードを生成
    InputDXL::CreatePadInstance(SysDef::PadNum);        // ゲームパッドを指定個数生成
    PadInputConfig::Create(SysDef::PadNum, true, true); // ゲームパッドのコンフィグを作成する

    FirstCreateTask();
}

//-----------------------------------------------------------------------------
// メインループ
void GameSystem::MainLoop()
{
    Fps fps;

    while (Run())
    {
        fps.Wait();
        fps.Update();

        // タスクが存在しなかった場合終了する
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
// 終了処理
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
// フルスクリーンモードにするか否かをメッセージボックスで問う
bool GameSystem::IsFullScreenMode()
{
    int flag;
    flag = MessageBox(
                NULL,
                TEXT("フルスクリーンモードで起動しますか？"),
                TEXT("スクリーン設定"),
                MB_YESNO | MB_ICONQUESTION);

    if (flag == IDYES) { return true; }
    return false;
}

//-----------------------------------------------------------------------------
// ループを回す際の判定処理
bool GameSystem::Run()
{
    return  ScreenFlip() == 0                               // 裏画面を表画面に反映
        &&  ProcessMessage() == 0                           // メッセージ処理
        &&  ClearDrawScreen() == 0                          // 画面をクリア
        &&  InputDXL::GetAllInputState()                    // 入力情報を取得
        &&  InputDXL::GetKey()[KEY_INPUT::ESCAPE] == OFF;   // ESCが押されていない
}

//-----------------------------------------------------------------------------
// 最初に作成するタスク
void GameSystem::FirstCreateTask()
{
    // タスクシステムを生成
    TaskSystem::Create();

    //☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
    // ゲーム開始時に作成するタスクを以下に記述 ※警告でるから(void)付けてね
    (void)Test::Task::Create();
}