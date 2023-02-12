#include "pch.h"

cmd_function_s* Cmd_FindCommand(const char* name)
{
    static const DWORD fnc = 0x4F9950;
    __asm
    {
        mov esi, name;
        call fnc;
    }
}
cmd_function_s* Cmd_AddCommand(char* cmdname, void(__cdecl* function)())
{
    cmd_function_s* cmd = Cmd_FindCommand(cmdname);

    if (cmd)
        return cmd;

    Com_Printf(CON_CHANNEL_CONSOLEONLY, "adding a new func command: %s\n", cmdname);


    static cmd_function_s _cmd{};

    __asm {
        push function;
        mov edi, offset _cmd;
        mov eax, cmdname;
        mov esi, 0x4F99A0;
        call esi;
        add esp, 4;
    }

    return 0;
}
cmd_function_s* Cmd_RemoveCommand(const char* cmdname)
{
    __asm
    {
        push cmdname;
        mov esi, 0x4F99E0;
        call esi;
        add esp, 0x4;
    }


}

//void Cmd_Init()
//{
//    std::cout << "calling Cmd_Init()\n";
//    Com_Printf(CON_CHANNEL_CONSOLEONLY, "loading custom cmd functions\n");
//    Cmd_AddCommand((char*)"1_kej_openmenu", OpenMenu_f);
//
//}
void Cbuf_AddText(const char* text, int localClientNum)
{
    __asm {
        mov eax, text;
        push eax;
        mov ecx, localClientNum;
        push ecx;
        mov esi, 0x530320;
        call esi;
        add esp, 0x8;
    }
}