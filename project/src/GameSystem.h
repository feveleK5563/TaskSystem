#pragma once

class GameSystem
{
public:
	GameSystem();

	void Initialize();	//初期化処理
	void MainLoop();	//メインループ
	void Finalize();	//終了処理

private:
	bool IsFullScreenMode();	//フルスクリーンモードにするか否かをメッセージボックスで問う
	bool Run();					//ループを回す際の判定処理

	void FirstCreateTask();		//最初に作成するタスク
};