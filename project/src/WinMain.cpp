#include <crtdbg.h>
#include "DxLib.h"
#include "GameSystem.h"
#include "Utility.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//アイコン変更
	SetWindowIconID(4210);

	//メモリリーク検出 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//デバッグ時にコンソール画面を出す
	ShowConsole();

	GameSystem gs;
	gs.Initialize();

	gs.MainLoop();

	gs.Finalize();
	return 0;
}
