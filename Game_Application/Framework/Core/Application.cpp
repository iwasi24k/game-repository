//==============================================================================
// File        : Application.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-13
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include <mmsystem.h>
#include <memory>
#include "Application.h"

// --- my library ---
#include "DebugTool.h"

// --- core ---
#include "Window.h"
#include "Timer.h"

// --- graphics ---
#include "Renderer.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "ModelManager.h"

// --- input ---
#include "InputKeyboard.h"
#include "InputMouse.h"

// --- scene ---
#include "SceneManager.h"
#include "Scene/Game/GameScene.h"

using namespace Framework;

Application::Application() {}
Application::~Application() { Finalize(); }

std::weak_ptr<Sprite> sprite;
std::weak_ptr<Model> model;

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
        LOG_EFF(L"Window Initialize Failed");
        return false;
    }
    m_hWnd = m_Window->GetHWnd();
    MSGBOX_INITIALIZE(m_hWnd);

    InputMouse::GetInstance().Initialize(m_hWnd);
    InputKeyboard::GetInstance().Initialize(m_hWnd);

	// --- renderer initialize ---
    if (!Renderer::GetInstance().Initialize(m_hWnd)) {
        LOG_EFF(L"Renderer Initialize Failed");
		return false;
    }

	// --- shader initialize ---
    if(!ShaderManager::GetInstance().Initialize(Renderer::GetInstance().GetDevice(), Renderer::GetInstance().GetContext())) {
        LOG_EFF(L"ShaderManager Initialize Failed");
        return false;
    }

    // --- game initialize ---
    if (!Init()) {
        LOG_EFF(L"Game Initialize Failed");
        return false;
    }

    LOG_IF(L"Application Initialize Completed");
    return true;
}

void Application::Shutdown() {
	LOG_IF(L"Application Shutdown..");
    Finalize();

    ShaderManager::GetInstance().Finalize();

    Renderer::GetInstance().Finalize();

    if (m_Window) { m_Window->Shutdown(); }

    LOG_SHUTDOWN;

    timeEndPeriod(1);
    CoUninitialize();
}

void Application::Run() {
	Timer::Reset();

    while (m_Window->ProcessMessage()) {
		Timer::Update();

        InputMouse::GetInstance().Update();
        InputKeyboard::GetInstance().Update();
        InputMouse::GetInstance().LockCursorCenter();
        Update();

		Renderer::GetInstance().BeginFrame();
        Draw();
		Renderer::GetInstance().EndFrame();
    }
}

// --- game loop ---
bool Application::Init() {
    ModelManager::GetInstance().Initialize();
    SpriteManager::GetInstance().Initialize();

	SceneManager::GetInstance().LoadScene(std::make_unique<GameScene>());

    return true;
}

void Application::Update() {
	SceneManager::GetInstance().Update();
}

void Application::Draw() {
	SceneManager::GetInstance().Draw();
}

void Application::Finalize() {
	SceneManager::GetInstance().UnloadScene();

	ModelManager::GetInstance().Finalize();
	SpriteManager::GetInstance().Finalize();
}