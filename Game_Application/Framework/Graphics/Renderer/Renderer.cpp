//==============================================================================
// File        : Renderer.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Renderer.h"
#include <stdexcept>

#include "Device.h"
#include "SwapChain.h"
#include "RenderTargetManager.h"
#include "DepthStencilState.h"
#include "ViewportManager.h"
#include "RasterizerStateManager.h"
#include "BlendStateManager.h"
#include "SamplerManager.h"
#include "ConstantBufferManager.h"

#include "DebugTool.h"

using namespace Framework;

Renderer::Renderer() {}
Renderer::~Renderer() {}

bool Renderer::Initialize(HWND hWnd) {
	// --- Device ---
    m_Device = std::make_unique<Device>();
    if (!m_Device->Initialize()) { 
        LOG_EFF(L"Device Initialize Failed");
        return false; 
    }

	// --- SwapChain ---
    m_SwapChain = std::make_unique<SwapChain>();
    if (!m_SwapChain->Initialize(hWnd, m_Device->GetDevice())) { 
        LOG_EFF(L"SwapChain Initialize Failed");
        return false; 
    }

	// --- RenderTarget ---
    m_RenderTargetManager = std::make_unique<RenderTargetManager>();
    if (!m_RenderTargetManager->Initialize(m_Device->GetDevice(), m_Device->GetContext(), m_SwapChain->GetSwapChain())) { 
        LOG_EFF(L"RenderTarget Initialize Failed");
        return false; 
    }

	// --- DepthStencil ---
    m_DepthStencilState = std::make_unique<DepthStencilState>();
    if (!m_DepthStencilState->Initialize(m_Device->GetDevice())) { 
        LOG_EFF(L"DepthStencil Initialize Failed");
        return false; 
    }

	// --- Viewport ---
    m_ViewportManager = std::make_unique<ViewportManager>();
    if (!m_ViewportManager->Initialize()) { 
        LOG_EFF(L"Viewport Initialize Failed");
        return false; 
    }

	// --- RasterizerState ---
    m_RasterizerStateManager = std::make_unique<RasterizerStateManager>();
    if (!m_RasterizerStateManager->Initialize(m_Device->GetDevice())) { 
        LOG_EFF(L"Rasterizer Initialize Failed");
        return false; 
    }

	// --- BlendState ---
    m_BlendStateManager = std::make_unique<BlendStateManager>();
    if (!m_BlendStateManager->Initialize(m_Device->GetDevice())) { 
        LOG_EFF(L"BlendState Initialize Failed");
        return false; 
    }

	// --- Sampler ---
    m_SamplerManager = std::make_unique<SamplerManager>();
    if (!m_SamplerManager->Initialize(m_Device->GetDevice())) { 
        LOG_EFF(L"Sampler Initialize Failed");
        return false; 
    }

	// --- ConstantBuffer ---
    m_ConstantBufferManager = std::make_unique<ConstantBufferManager>();
    if (!m_ConstantBufferManager->Initialize(m_Device->GetDevice())) { 
        LOG_EFF(L"ConstantBuffer Initialize Failed");
        return false; 
    }

	LOG_IF(L"Renderer Initialize Completed");
    return true;
}

void Renderer::Finalize() {
    LOG_IF(L"Renderer Shutdown..");

    if (m_ConstantBufferManager) {
		LOG_IF(L"ConstantBuffer Finalize..");
        m_ConstantBufferManager->Finalize();
        m_ConstantBufferManager.reset();
    }

    if (m_SamplerManager) {
		LOG_IF(L"Sampler Finalize..");
        m_SamplerManager->Finalize();
        m_SamplerManager.reset();
    }

    if (m_BlendStateManager) {
		LOG_IF(L"BlendState Finalize..");
        m_BlendStateManager->Finalize();
        m_BlendStateManager.reset();
    }

    if (m_RasterizerStateManager) {
		LOG_IF(L"RasterizerState Finalize..");
        m_RasterizerStateManager->Finalize();
        m_RasterizerStateManager.reset();
    }

    if (m_ViewportManager) {
		LOG_IF(L"ViewportManager Finalize..");
        m_ViewportManager->Finalize();
        m_ViewportManager.reset();
    }

    if (m_DepthStencilState) {
		LOG_IF(L"DepthStencilState Finalize..");
        m_DepthStencilState->Finalize();
        m_DepthStencilState.reset();
    }

    if (m_RenderTargetManager) {
		LOG_IF(L"RenderTargetManager Finalize..");
        m_RenderTargetManager->Finalize();
        m_RenderTargetManager.reset();
    }

    if (m_SwapChain) {
		LOG_IF(L"SwapChain Finalize..");
        m_SwapChain->Finalize();
        m_SwapChain.reset();
    }

    if (m_Device) {
		LOG_IF(L"Device Finalize..");
        m_Device->Finalize();
        m_Device.reset();
    }
}


void Renderer::BeginFrame() {
    float clearColor[4] = { 0.1f, 0.1f, 0.2f, 1.0f };

    auto context = m_Device->GetContext();

    m_RenderTargetManager->Clear(context, clearColor);

    m_RenderTargetManager->Bind(context);

    m_ViewportManager->Bind(context);

    m_BlendStateManager->Apply(context, false);

    m_SamplerManager->Bind(context);

    m_RasterizerStateManager->Apply(context, false);
}

void Renderer::EndFrame() {
    m_SwapChain->Present();
}

void Renderer::SetDepthEnable(bool enable) {
    m_DepthStencilState->Bind(m_Device->GetContext(), enable);
}

void Renderer::SetDepthWriteEnable(bool enable) {
    m_DepthStencilState->WriteBind(m_Device->GetContext(), enable);
}

void Renderer::SetCullEnable(bool enable) {
    m_RasterizerStateManager->Apply(m_Device->GetContext(), enable);
}

void Renderer::SetRasterizerEnable(bool enable) {
    m_RasterizerStateManager->Apply(m_Device->GetContext(), enable);
}

void Renderer::SetBlendEnable(bool enable) {
    m_BlendStateManager->Apply(m_Device->GetContext(), enable);
}

void Renderer::SetSampler(UINT slot) {
	m_SamplerManager->SetSampler(slot, nullptr, m_Device->GetContext());
}

void Renderer::SetMatrix(math::matrix world, math::matrix view, math::matrix projection) {
    Shader::MatrixBuffer vpData;

    vpData.World = world;
    vpData.View = view;
    vpData.Projection = projection;

    m_ConstantBufferManager->Update(m_Device->GetContext(), vpData, 0, Shader::ShaderStage::Vertex);
}

void Renderer::SetLight(math::vector4f direction, math::vector4f diffuse, math::vector4f ambient, math::vector4f position, math::vector4f pointLightParam) {
    Shader::LightBuffer lpData;

    lpData.Direction = direction;
    lpData.Diffuse = diffuse;
    lpData.Ambient = ambient;
    lpData.Position = position;
    lpData.PointLightParam = pointLightParam;   

    m_ConstantBufferManager->Update(m_Device->GetContext(), lpData, 1, Shader::ShaderStage::Pixel);

}

void Renderer::SetMaterial(math::vector4f ambient, math::vector4f diffuse, math::vector4f specular, math::vector4f emission, float shininess, bool textureEnable) {
    Shader::MaterialBuffer mb{};
    mb.Ambient = ambient;
    mb.Diffuse = diffuse;
    mb.Specular = specular;
    mb.Emission = emission;
    mb.Shininess = shininess;
    mb.TextureEnable = textureEnable;

    m_ConstantBufferManager->Update(m_Device->GetContext(), mb, 2, Shader::ShaderStage::Pixel);
}

void Renderer::SetColor(math::vector4f color) {
    Shader::ColorBuffer cb{};
    cb.Color = color;

    m_ConstantBufferManager->Update(m_Device->GetContext(), cb, 3, Shader::ShaderStage::Pixel);
}

ID3D11Device* Renderer::GetDevice() const {
    return m_Device->GetDevice();
}

ID3D11DeviceContext* Renderer::GetContext() const {
    return m_Device->GetContext();
}

ConstantBufferManager* Renderer::GetConstantBuffer() { 
    return m_ConstantBufferManager.get(); 
}
