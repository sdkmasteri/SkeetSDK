#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "skeetsdk.h"

static void UnSetVisibles()
{
    SkeetSDK::ForEach(SkeetSDK::GetChild(Misc, 2), [](Element* element) {
        SkeetSDK::SetVisible(element, true);
        });
}

static void LoadConfig()
{
    SkeetSDK::LoadCfg();
}

static void SetMenuKey(int KEY)
{
    SkeetSDK::SetHotkey(SkeetSDK::GetElement<Hotkey>(SkeetSDK::GetChild(Misc, 2), 1), KEY);
}

static void PrintAllLuas()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    SkeetSDK::InitConfig();
    int Luacount = SkeetSDK::LuaCount();
    for (int i = 0; i < Luacount; i++)
    {
        printf("Lua #%d: %ls\n", i, SkeetSDK::LuaName(i));
    }
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    SkeetSDK::WaitForMenu();
    UnSetVisibles();
    LoadConfig();
    SetMenuKey(VK_INSERT);
    SkeetSDK::SetTab(Config);
    SkeetSDK::AllowUnsafe(1);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}