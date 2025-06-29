#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "skeetsdk.h"

#include "includes.h"

#ifdef _WIN64
#define GWL_WNDPROC GWLP_WNDPROC
#endif


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
static bool isOpen = false;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	if (GetAsyncKeyState(VK_INSERT) & 1)
		isOpen =! isOpen;

	static bool showhidden = false;
	if (isOpen) {
		ImGui::Begin("Window");
		ImGui::Checkbox("Show hidden", &showhidden);
		ImGui::End();
	}

	// TODO: Fix so trash example of impl imgui
	if (showhidden) {
		Skeet.ForEach<void(*)(Element*)>(Skeet.Menu->Tabs->Misc->Childs[2]->Elements, [](Element* element) {
		Skeet.SetVisible(element, true);
		});
	} else {
		Skeet.ForEach<void(*)(Element*)>(Skeet.Menu->Tabs->Misc->Childs[2]->Elements, [](Element* element) {
		Skeet.SetVisible(element, false);
		});
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}


DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		Skeet.WaitForMenu();
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)& oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}

// static void UnSetVisibles()
// {
//     Skeet.ForEach<void(*)(Element*)>(Skeet.Menu->Tabs->Misc->Childs[2]->Elements, [](Element* element) {
//         Skeet.SetVisible(element, true);
//         });
// }
//
// static void LoadConfig()
// {
//     Skeet.LoadCfg();
// }
//
// static void SetMenuKey(int KEY)
// {
//     Skeet.SetHotkey(&Skeet.Menu->Tabs->Misc->Childs[2]->Elements[1]->hotkey, KEY);
// }
//
// DWORD WINAPI MainThread(LPVOID lpParam)
// {
//     Skeet.WaitForMenu();
//     UnSetVisibles();
//     LoadConfig();
//     SetMenuKey(VK_INSERT);
//     return 0;
// }
//
// BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
// {
//
//     if (fdwReason == DLL_PROCESS_ATTACH)
//         CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
//
//     return TRUE;
// }