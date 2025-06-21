// Exmaple of using SkeetSDK
#include <Windows.h>
#include <stdio.h>
#include "Skeet.h"

// Unhide hiden checkboxes in Misc->Settings
static void UnhideElements()
{
    for (int i = 0; i < 20; i++)
        Skeet.SetVisible(Skeet.menu->Tabs->Misc->Childs[2]->Elements[i], 1);
    Skeet.Callback(Skeet.menu->Tabs->Misc->Childs[2]->Elements[11]);
}

// Loads first cfg in list
static void LoadConfig()
{
    Skeet.LoadCfg();
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Skeet.WaitForMenu();
    UnhideElements();
	LoadConfig();
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}