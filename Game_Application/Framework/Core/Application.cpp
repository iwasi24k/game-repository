//==============================================================================
// File        : Application.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// game loop ÉQÅ[ÉÄ
//==============================================================================
#include "pch.h"
#include <mmsystem.h>

// --- core ---
#include "Application.h"
#include "Window.h"
#include "Timer.h"

using namespace Framework;

Application::Application() {}
Application::~Application() { Finalize(); }


bool Application::Initialize(HINSTANCE hInstance, int nCmdShow) {
    CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    timeBeginPeriod(1);

    Timer::Initialize();

	// --- window initialize ---
    m_Window = std::make_unique<Window>();
    if (!m_Window->Initialize(hInstance, nCmdShow)) {
        return false;
    }
    m_hWnd = m_Window->GetHWnd();

    // --- game initialize ---
    if (!Init()) {
        return false;
    }

    return true;
}

void Application::Shutdown() {
    Finalize();

    if (m_Window) m_Window->Shutdown();

    timeEndPeriod(1);
    CoUninitialize();
}

void Application::Run() {
	Timer::Reset();

    while (m_Window->ProcessMessage()) {
		Timer::Update();

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