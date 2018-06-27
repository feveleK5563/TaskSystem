#include <crtdbg.h>
#include "DxLib.h"
#include "GameSystem.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ƒƒ‚ƒŠƒŠ[ƒNŒŸo
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameSystem gs;
	gs.Initialize();

	gs.MainLoop();

	gs.Finalize();
	return 0;
}
