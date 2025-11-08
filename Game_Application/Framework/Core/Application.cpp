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
#include "Application.h"

// --- my library ---
#include "DebugTool.h"

// --- core ---
#include "Window.h"
#include "Timer.h"

using namespace Framework;

Application::Application() {}
Application::~Application() { Finalize(); }


bool Application::Initialize(HINSTANCE hInstance, int nCmdShow) {
    CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
    timeBeginPeriod(1);

	// --- log initialize ---
    LOG_INITIALIZE;
    LOG_IF(L"Application Initialize Start");

	// --- timer initialize ---
    Timer::Initialize();

	// --- window initialize ---
    m_Window = std::make_unique<Window>();
    if (!m_Window->Initialize(hInstance, nCmdShow)) {
        LOG_EFF(L"Window Initialize Failure");
        return false;
    }
    m_hWnd = m_Window->GetHWnd();
    MSGBOX_INITIALIZE(m_hWnd);

    // --- game initialize ---
    if (!Init()) {
        LOG_EFF(L"Game Initialize Failure");
        return false;
    }

    LOG_IF(L"Application Initialize Completed");
    return true;
}

void Application::Shutdown() {
	LOG_IF(L"Application Shutdown..");
    Finalize();

    if (m_Window) m_Window->Shutdown();

    LOG_SHUTDOWN;

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