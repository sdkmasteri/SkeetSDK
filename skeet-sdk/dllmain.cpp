#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SDK_DETOUR_IMP
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

CryptFn Prologue = NULL;
void __fastcall hk(wchar_t* str, size_t bsize, int step)
{
    printf("%ls\n", str);
    Prologue(str, bsize, step);
};

// "51 53 8B 5C 24 0C 55 56 8B E9" - CryptSignature
void hookCryptMethod()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    SigFinder schunk((LPVOID)0x43310000, 0x2FC000u); // scan on skeet mapped chunk
    Prologue = (CryptFn)DHook.Hook(schunk.find("51 53 8B 5C 24 0C 55 56 8B E9"), hk, 6)->Naked();
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    SkeetSDK::WaitForMenu();
    UnSetVisibles();
    LoadConfig();
    SetMenuKey(VK_INSERT);
    SkeetSDK::AllowUnsafe(true);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}