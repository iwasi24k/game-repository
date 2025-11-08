//==============================================================================
// File        : SamplerManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるテクスチャサンプラーステートを管理します。
// サンプラーはテクスチャの読み取り方法（拡大縮小、繰り返し、補間方法など）を定義する設定です。
// Initialize() で基本的な線形フィルタとラップ設定を持つサンプラーを作成し、
// Bind() や SetSampler() で描画時に GPU に適用します。
// Finalize() で作成したサンプラーステートを解放し、GPU リソースを安全に管理します。
// このクラスにより、テクスチャの描画を滑らかで安定した見た目に保つことができます。
//==============================================================================
#ifndef SAMPLER_MANAGER_H
#define SAMPLER_MANAGER_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

	class SamplerManager {
	private:
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SamplerState;

	public:
		SamplerManager();
		~SamplerManager();

		bool Initialize(ID3D11Device* device);
		void Finalize();

		void Bind(ID3D11DeviceContext* context);
		void SetSampler(UINT slot, ID3D11SamplerState* sampler, ID3D11DeviceContext* context);
	};
}

#endif // SAMPLER_MANAGER_H