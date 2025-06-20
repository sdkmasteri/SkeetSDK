// Exmaple of using SkeetSDK
// Unhide hiden checkboxes in Misc->Settings
#include <Windows.h>
#include <stdio.h>
#include "Skeet.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
    Menu* MenuPTR = (Menu*)0x434799AC;
    while (!MenuPTR->Pos.x) Sleep(100);
    for (int i = 12; i < 20; i++)
        MenuPTR->Tabs->Misc->Childs[2]->Elements[i]->header.Flags.Visible = 1;

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}