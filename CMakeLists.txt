cmake_minimum_required(VERSION 3.31)
project(skeetsdk)

set(CMAKE_CXX_STANDARD 14)

add_library(skeet_extended SHARED skeet-sdk/dllmain.cpp
        skeet-sdk/skeetsdk.h)
