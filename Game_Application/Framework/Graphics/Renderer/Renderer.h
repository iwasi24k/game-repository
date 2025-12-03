//==============================================================================
// File        : Renderer.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-12-03
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 の描画基盤を統括的に制御するレンダラーです。
// Device・SwapChain・RenderTarget・DepthStencil・Rasterizer・BlendState・Sampler など、
// 描画パイプラインを構成するすべてのマネージャを初期化・解放・適用する役割を担います。
// BeginFrame() により描画前のクリア・状態設定を行い、EndFrame() でフレームを画面へ転送。
// また各種ステート（深度・ラスタライザ・ブレンド・サンプラ等）を柔軟に切り替え可能です。
// 本クラスは “フレーム全体の制御中枢” として、描画処理の統一管理を目的としています。
//==============================================================================
#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include "MathTransform.h"
#include "ShaderTypes.h"
#include "Device.h"
#include "ConstantBufferManager.h"

namespace Framework {

	class Renderer {
	private:
		std::unique_ptr<class Device> m_Device;
		std::unique_ptr<class SwapChain> m_SwapChain;
		std::unique_ptr<class RenderTargetManager> m_RenderTargetManager;
		std::unique_ptr<class DepthStencilState> m_DepthStencilState;
		std::unique_ptr<class SamplerManager> m_SamplerManager;
		std::unique_ptr<class ViewportManager> m_ViewportManager;
		std::unique_ptr<class ConstantBufferManager> m_ConstantBufferManager;
		std::unique_ptr<class RasterizerStateManager> m_RasterizerStateManager;
		std::unique_ptr<class BlendStateManager> m_BlendStateManager;

		Renderer();
		~Renderer();
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

	public:
		static Renderer& GetInstance() {
			static Renderer instance;
			return instance;
		}

		bool Initialize(HWND hWnd);
		void Finalize();

		void BeginFrame();
		void EndFrame();

		void SetDepthEnable(bool enable);
		void SetDepthWriteEnable(bool enable);
		void SetCullEnable(bool enable);
		void SetRasterizerEnable(bool enable);
		void SetBlendEnable(bool enable);
		void SetSampler(UINT slot);
		void SetMatrix(math::matrix world, math::matrix view, math::matrix projection);
		void SetLight(math::vector4f direction, math::vector4f diffuse, math::vector4f ambient, math::vector4f position, math::vector4f pointLightParam);
		void SetMaterial(math::vector4f ambient, math::vector4f diffuse, math::vector4f specular, math::vector4f emission, float shininess, bool textureEnable);
		void SetColor(math::vector4f color);

		template<typename T>
		void SetBuffer(UINT slot, T data, Shader::ShaderStage stage) {
			m_ConstantBufferManager->Update(m_Device->GetContext(), data, slot, stage);
		}

		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetContext() const;

		ConstantBufferManager* GetConstantBuffer();
	};
}

#endif // RENDERER_H