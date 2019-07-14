#include <crtdbg.h>
#include "DxLib.h"
#include "GameSystem.h"
#include "Utility.h"


int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
    //�A�C�R���ύX
    SetWindowIconID(4210);

    //���������[�N���o 
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    //�f�o�b�O���ɃR���\�[����ʂ��o��
    ShowConsole();

    GameSystem gs;
    gs.Initialize();

    gs.MainLoop();

    gs.Finalize();
    return 0;
}
