//==============================================================================
// File        : Application.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include <mmsystem.h>
#include "Application.h"

// --- my library ---
#include "DebugTool.h"

// --- core ---
#include "Window.h"
#include "Timer.h"

// --- graphics ---
#include "Renderer.h"
#include "ShaderManager.h"
#include "Sprite.h"
#include "TextureManager.h"

using namespace Framework;

Application::Application() {}
Application::~Application() { Finalize(); }
Sprite sprite;


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

        Update();

		Renderer::GetInstance().BeginFrame();
        Draw();
		Renderer::GetInstance().EndFrame();
    }
}

// --- game loop ---
bool Application::Init() {
    ShaderManager::GetInstance().LoadVS(L"SpriteShader", L"cso-file\\SpriteVS.cso", Shader::VertexLayoutType::Sprite);
    ShaderManager::GetInstance().LoadPS(L"SpriteShader", L"cso-file\\SpritePS.cso");

    auto texture = TextureManager::GetInstance().LoadTexture(L"Asset\\Texture\\nazuna.png");

    // スプライト初期化
    sprite.Initialize();
    sprite.SetTexture(texture);
    sprite.SetTransform({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
    //sprite.SetSize( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );
    //sprite.SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//sprite.SetUV(0.0f, 0.0f, 1.0f, 1.0f);
    //sprite.SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

    return true;
}

void Application::Update() {

}

void Application::Draw() {
    ShaderManager::GetInstance().SetShader(L"SpriteShader");
	sprite.Draw();
}

void Application::Finalize() {
	sprite.Finalize();
}