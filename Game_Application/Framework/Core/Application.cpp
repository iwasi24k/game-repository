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
	//SceneManager::GetInstance().LoadScene(std::make_uniqe<初期シーンの設定>());
    
    ShaderManager::GetInstance().LoadVS(L"SpriteShader", L"cso-file\\SpriteVS.cso", Shader::VertexLayoutType::Sprite);
    ShaderManager::GetInstance().LoadPS(L"SpriteShader", L"cso-file\\SpritePS.cso");

    // スプライト初期化
    SpriteManager::GetInstance().Initialize();
	sprite = SpriteManager::GetInstance().LoadSprite(L"Asset\\Texture\\nazuna.png");
    sprite.lock()->SetTransform({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
    //sprite.lock()->SetSize( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );
    //sprite.lock()->SetSize(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//sprite.lock()->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
    //sprite.lock()->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

    ShaderManager::GetInstance().LoadVS(L"ModelShader", L"cso-file\\VertexShader.cso");
    ShaderManager::GetInstance().LoadPS(L"ModelShader", L"cso-file\\PixelShader.cso");

	ModelManager::GetInstance().Initialize();
	model = ModelManager::GetInstance().LoadModel(L"Asset/Model/cube.fbx");
    model.lock()->SetTransform({1.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {-IX_PI / 1.5f, 0.0f, 0.0f});
    
    return true;
}

void Application::Update() {
	//SceneManager::GetInstance().Update();
    if (InputMouse::GetInstance().IsMouseClicked(MB::Left))
		sprite.lock()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		//sprite.lock()->SetTransform({ SCREEN_WIDTH, SCREEN_HEIGHT }, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
	if (InputKeyboard::GetInstance().IsKeyTriggered(KB::R))
		model.lock()->SetTransform({1.0f, 1.0f, 1.0f}, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f });
}

void Application::Draw() {
	//SceneManager::GetInstance().Draw();
    ShaderManager::GetInstance().SetShader(L"SpriteShader");
	Renderer::GetInstance().SetDepthEnable(false);

	sprite.lock()->Draw();

    ShaderManager::GetInstance().SetShader(L"ModelShader");
	Renderer::GetInstance().SetDepthEnable(true);
    math::matrix view = math::matrix::LookAtLH(
        { 0.0f, 0.0f, -5.0f }, // eye
        { 0.0f, 0.0f, 0.0f },  // at
        { 0.0f, 1.0f, 0.0f }   // up
    );
    math::matrix proj = math::matrix::PerspectiveFovLH(
        DirectX::XMConvertToRadians(60.0f),
        static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
        0.1f, 100.0f
    );
    Renderer::GetInstance().SetLight(
        { -0.5f, -1.0f, -0.5f, 0.0f }, // direction
        { 1.0f, 1.0f, 1.0f, 1.0f },    // diffuse
        { 0.2f, 0.2f, 0.2f, 1.0f },    // ambient
        { 0.0f, 0.0f, -5.0f, 1.0f },   // position
        { 1.0f, 0.1f, 0.0f, 0.0f }     // pointLightParam (range, attenuation, unused, unused)
	);
	Renderer::GetInstance().SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	model.lock()->Draw(view, proj);
}

void Application::Finalize() {
	//SceneManager::GetInstance().UnloadScene();
	ModelManager::GetInstance().Finalize();
	SpriteManager::GetInstance().Finalize();
}