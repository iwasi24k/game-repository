//==============================================================================
// File        : main.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview : 
// DirectX main loop
// ApplicationåƒÇ—èoÇµ
//==============================================================================
#include "pch.h"
#include "Framework/Core/Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    Framework::Application app;

    if (!app.Initialize(hInstance, nCmdShow)) { return -1; }

    app.Run();
    app.Shutdown();

    return 0;
}
