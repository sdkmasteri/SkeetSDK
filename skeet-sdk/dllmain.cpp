#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SDK_RENDERER_IMP
#define SDK_GLOBALS_IMP
#define SDK_CLIENT_IMP
#include "skeetsdk.h"
#include <chrono>
#include <ctime>
#include <cmath>

static void UnSetVisibles();
static void LoadConfig();
static void SetMenuKey(int KEY);
static void PrintAllLuas();
static void Watermark();
static void __vectorcall MMLerp(float& a, float min, float max, float& t, float speed);

using namespace SkeetSDK;

DWORD WINAPI MainThread(LPVOID lpParam)
{
    UnSetVisibles();
    LoadConfig();
    SetMenuKey(VK_INSERT);
    Utils::AllowUnsafe(true);
    Watermark();
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{

    if (fdwReason == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);

    return TRUE;
}


//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
static void UnSetVisibles()
{
    Utils::ForEach(UI::GetChild(Misc, 2), [](PElement element) {
        UI::SetVisible(element, true);
        });
}

static void LoadConfig()
{
    Utils::LoadCfg();
}

static void SetMenuKey(int KEY)
{
    UI::SetHotkey(UI::GetElement<Hotkey>(UI::GetChild(Misc, 2), 1), KEY);
}

static void PrintAllLuas()
{
    Utils::InitConfig();
    int Luacount = Utils::LuaCount();
    for (int i = 0; i < Luacount; i++)
    {
        Client::LogColor({ 255, 255, 255, 255 }, "Lua #%d: %ls\n", i, Utils::LuaName(i));
    }
}


static void __vectorcall MMLerp(float& a, float min, float max, float& t, float speed)
{
    t += speed;
    float s = (sinf(t) + 1.f) * 0.5f;

    a = min + (max - min) * s;
};

float alpha = 255.f;
float t = 0.f;
static void WatermarkEvent()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&currentTime);
    wchar_t timestr[128];
    const wchar_t* name = L"SkeetSDK";
    swprintf_s(timestr, sizeof(timestr) / sizeof(wchar_t), L" | %02d:%02d:%02d | %d fps", localTime->tm_hour, localTime->tm_min, localTime->tm_sec,
        (int)(1 / Globals::FrameTime(true)));
    const unsigned int flags = TEXT_FLAG_DEFAULT;
    Vec2 strsize = Renderer::MeasureText((wchar_t*)name, flags);
    Vec2 timesize = Renderer::MeasureText(timestr, flags);
    int w = Renderer::ScreenWidth();
    Vec2 pos = { w - (strsize.x + timesize.x) - 40, 10 };
    Vec2 rsize = { strsize.x + timesize.x + 20, strsize.y * 2 };
    int arr[] = { pos.x, pos.y, rsize.x, rsize.y };
    Renderer::Rect(pos, rsize, { 12, 12, 12, 160 });
    VecCol mcol(UI::GetMenuCol());
    MMLerp(alpha, 60.f, 255.f, t, 5.f * Globals::FrameTime());
    mcol.a = (unsigned char)alpha;
    Renderer::Text({ pos.x + 10, pos.y + strsize.y / 2 }, mcol, (wchar_t*)name, flags);
    Renderer::Text({ pos.x + strsize.x + 10, pos.y + strsize.y / 2 }, { 0xFFFFFFFF }, timestr, flags);
};

static void Watermark()
{
    Renderer::Init();
    Renderer::AddEvent(REVENT_FINAL, WatermarkEvent);
};