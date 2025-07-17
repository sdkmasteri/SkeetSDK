#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define _SDK_PUBLIC_UNSAFE_MEMBERS
#define SDK_DETOUR_IMP
#include "skeetsdk.h"
#include <string>
#include <iostream>

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
    SkeetSDK::InitConfig();
    int Luacount = SkeetSDK::LuaCount();
    for (int i = 0; i < Luacount; i++)
    {
        SkeetSDK::CPrintf({255, 255, 255, 255}, "Lua #%d: %ls\n", i, SkeetSDK::LuaName(i));
    }
}

CryptFn ogCryptfn = NULL;
static void __fastcall CyrptHook(wchar_t* str, size_t bsize, int step)
{
    printf("%ls\n", str);
    ogCryptfn(str, bsize, step);
};

// "51 53 8B 5C 24 0C 55 56 8B E9" - CryptSignature
static void hookCryptMethod()
{
    SigFinder schunk((LPVOID)0x43310000, 0x2FC000u); // scan on skeet mapped chunk
    ogCryptfn = (decltype(ogCryptfn))DHook.Hook(schunk.find("51 53 8B 5C 24 0C 55 56 8B E9"), CyrptHook, 6)->Naked();
}

// TextRender HOOK
static int InBox(Listbox* list, wchar_t* elem)
{
    for (size_t i = 0; i < list->ItemsCount; i++)
    {
        if (wcscmp(list->Info.ItemsChunk[i].NameChunk + 1, elem) == 0) return i;
    };
    return -1;
};

typedef void(__fastcall* TextRender)(void*, int, int, int, int, int, wchar_t*, size_t);
TextRender ogTextRender = NULL;
int ctext = 0;
Listbox* box = NULL;
Textbox* t1 = NULL;
Textbox* t2 = NULL;
sVec<wchar_t*> custom(255);

static void __fastcall ButtonHandle(void* ecx, void* edx)
{
    size_t tsze = (t1->Length + 2) * sizeof(wchar_t);

    wchar_t* text = (wchar_t*)malloc(tsze);
    memset(text, 0x00, tsze);
    text[0] = (wchar_t)L'*';
    memcpy(text + 1, t1->Text, tsze - sizeof(wchar_t) * 2);

    SkeetSDK::AddListboxVar(box, text, tsze);
    free(text);

    size_t bsze = (t2->Length + 1) * sizeof(wchar_t);
    wchar_t* ptr = (wchar_t*)malloc(bsze);
    memset(ptr, 0x00, bsze);
    memcpy(ptr, t2->Text, bsze - sizeof(wchar_t));
    custom.Push(ptr);
    t1->Length = 0;
    t2->Length = 0;
};

static void __fastcall ButtonHandleD(void* ecx, void* edx)
{
    if (!box->ItemsCount || !custom.Lenght()) return;
    custom.Removef(box->Info.SelectedItem);
    SkeetSDK::RemoveListboxVar(box, box->Info.SelectedItem);
};

static void __fastcall TextRenderHook(void* ths, int id, int x, int y, int color, int somint, wchar_t* text, size_t len)
{
    //printf("POS: %d | %d\n", x, y);
    //printf("COLOR: %x\nINT: %d\n", color, somint);
    //printf("THIS: %p\nEDX: %d\n", ths, id);
    //printf("%ls | len: %d\n", text, len);
    int mcol = SkeetSDK::GetMenuCol().pack();
    int i = color == mcol ? InBox(box, text+1) : InBox(box, text);
    if (i >= 0)
    {
        text = (wchar_t*)custom[i];
        len = wcslen(text);
    }

    ogTextRender(ths, id, x, y, color, somint, text, len);
}

static void hookTextRender()
{
    CTab* tab = SkeetSDK::CreateTab((wchar_t*)L"Textor", { 6, 20 + 64 * 9 });
    Child* child = SkeetSDK::CreateChild(tab, (wchar_t*)L"Text", { 0x00, 0x24, 0x00, 0x24 }, false);
    box = SkeetSDK::CreateListbox(child, (wchar_t*)L"Strings", &ctext, NULL, NULL, true);
    t1 = SkeetSDK::CreateTextbox(child, false, (wchar_t*)L"Original");
    t2 = SkeetSDK::CreateTextbox(child, false, (wchar_t*)L"Custom");
    SkeetSDK::CreateButton(child, (wchar_t*)L"Add redefine", ButtonHandle, NULL);
    SkeetSDK::CreateButton(child, (wchar_t*)L"Delete redefine", ButtonHandleD, NULL);
    SigFinder schunk((LPVOID)0x43310000, 0x2FC000u);
    ogTextRender = (decltype(ogTextRender))DHook.Hook(schunk.find("55 8B EC 53 56 8B 75 1C"), TextRenderHook)->Naked();
}
// TextRender HOOK end

// Print console HOOK
typedef void(__thiscall* LuaPrint)(char*);
LuaPrint ogPrintfn = NULL;

static void __fastcall PrintHook(char* ecx)
{
    printf("%s\n", ecx);
    ogPrintfn(ecx);
};

static void hookPrint()
{
    ogPrintfn = (decltype(ogPrintfn))DHook.Hook((LPVOID)0x4341CDD9, PrintHook, 6)->Naked();
}
// Print console HOOK end

DWORD WINAPI MainThread(LPVOID lpParam)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
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