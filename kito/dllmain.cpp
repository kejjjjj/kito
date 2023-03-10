// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        //CreateThread(0, 0, (LPTHREAD_START_ROUTINE)parent_thread, hModule, 0, 0);
        thread = std::thread((LPTHREAD_START_ROUTINE)parent_thread, hModule);
        thread.detach();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

