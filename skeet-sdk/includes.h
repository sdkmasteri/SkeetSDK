//
// Created by sol on 6/28/2025.
//

#ifndef INCLUDES_H
#define INCLUDES_H
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <kiero.h>
#include <MinHook.h>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>
#define WINDOW_NAME "Dear ImGui DirectX9 Example"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

#endif //INCLUDES_H
