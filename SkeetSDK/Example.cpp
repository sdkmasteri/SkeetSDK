// Exmaple of using SkeetSDK
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "Skeet.h"

// Unhide hiden checkboxes in Misc->Settings
static void UnSetVisibles()
{
    Skeet.ForEach<void(*)(Element*)>(Skeet.menu->Tabs->Misc->Childs[2]->Elements, [](Element* element) {
        Skeet.SetVisible(element, true);
	});
}

// Loads first cfg in list
static void LoadConfig()
{
    Skeet.LoadCfg();
}

// Sets the menu hotkey
static void SetMenuKey(int KEY)
{
    Skeet.SetHotkey(&Skeet.menu->Tabs->Misc->Childs[2]->Elements[1]->hotkey, KEY);
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Skeet.WaitForMenu();
    UnSetVisibles();
    LoadConfig();
    SetMenuKey(VK_INSERT);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}