//==============================================================================
// File        : Application.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-06
//------------------------------------------------------------------------------
// Overview :
// game loop ÉQÅ[ÉÄ
//==============================================================================
#include "pch.h"
#include "Application.h"

using namespace Framework;

Application::Application() {}
Application::~Application() { Finalize(); }


bool Application::Initialize(HINSTANCE hInstance, int nCmdShow) {
    CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

    m_Window = std::make_unique<Window>();
    if (!m_Window->Initialize(hInstance, nCmdShow)) {
        return false;
    }

    m_hWnd = m_Window->GetHWnd();

    // --- game init ---
    if (!Init()) {
        return false;
    }

    return true;
}

void Application::Shutdown() {
    Finalize();
    if (m_Window) m_Window->Shutdown();
    CoUninitialize();
}

void Application::Run() {
    while (m_Window->ProcessMessage()) {
        Update();
        Draw();
    }
}

// --- game loop ---
bool Application::Init() {

    return true;
}

void Application::Update() {

}

void Application::Draw() {

}

void Application::Finalize() {
    
}