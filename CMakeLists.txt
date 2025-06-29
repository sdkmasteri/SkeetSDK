cmake_minimum_required(VERSION 3.31)
project(skeetsdk)

set(CMAKE_CXX_STANDARD 14)

set(MINHOOK_SRC
        skeet-sdk/libs/kiero/minhook/src/buffer.c
        skeet-sdk/libs/kiero/minhook/src/hook.c
        skeet-sdk/libs/kiero/minhook/src/trampoline.c
        skeet-sdk/libs/kiero/minhook/src/hde/hde32.c)

set(KIERO_SRC skeet-sdk/libs/kiero/kiero.cpp)
set(IMGUI_SRC
        skeet-sdk/libs/imgui/imgui.cpp
        skeet-sdk/libs/imgui/imgui_widgets.cpp
        skeet-sdk/libs/imgui/imgui_tables.cpp
        skeet-sdk/libs/imgui/imgui_draw.cpp
        skeet-sdk/libs/imgui/backends/imgui_impl_dx9.cpp
        skeet-sdk/libs/imgui/backends/imgui_impl_win32.cpp
        skeet-sdk/includes.h)
include_directories(skeet-sdk/libs/imgui
        skeet-sdk/libs/imgui/backends
        skeet-sdk/libs/kiero/minhook/include
        skeet-sdk/libs/kiero
        $ENV{DXSDK_DIR}/Include
)


add_library(skeet_extended SHARED ${MINHOOK_SRC} ${KIERO_SRC} ${IMGUI_SRC} skeet-sdk/dllmain.cpp
        skeet-sdk/skeetsdk.h)
