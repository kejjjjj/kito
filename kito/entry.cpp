#include "pch.h"


DWORD WINAPI parent_thread(HMODULE hModule)
{

    auto iw3sp = (DWORD)GetModuleHandleA(GAME_MODULE);

    if (!iw3sp) {
        return 0;
    }

    while (!cg::dx->device) {
        std::this_thread::sleep_for(100ms);
    }
    std::this_thread::sleep_for(500ms);

    FILE* _con = 0;

    AllocConsole();
    freopen_s(&_con, "CONOUT$", "w", stdout);

    std::cout << "hello, world!\n";



    cg::CG_Init();

	while (!(GetAsyncKeyState(VK_HOME)&1))
	{
		Sleep(300);
	}

    cg::CG_Cleanup();

    std::cout << "Goodbye!\n";


    Sleep(500);
    if (_con)
        fclose(_con);
    FreeConsole();
   
    FreeLibraryAndExitThread(hModule, 0);
	return 1;
}