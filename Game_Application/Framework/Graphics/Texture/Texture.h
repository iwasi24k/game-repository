//==============================================================================
// File        : Texture.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるテクスチャ管理を担当します。
// ファイル（PNG、JPG、BMP など）を読み込み、GPU 上に Shader Resource View を作成。
// シェーダーから直接参照できる状態に変換し、描画時にテクスチャを適用可能。
// Initialize()/Finalize() でリソースの準備・解放を行い、Load() でファイルを読み込む。
// GetSRV()/SetSRV() により外部との SRV 共有や差し替えもサポート。
//==============================================================================
#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>
#include <wrl/client.h>
#include <string>

namespace Framework {

	class Texture {
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;

	public:
		Texture();
		~Texture();

		bool Initialize();
		void Finalize();

		bool Load(const std::wstring& filePath);

		void SetSRV(ID3D11ShaderResourceView* srv);
		ID3D11ShaderResourceView* GetSRV() const; 
	};
}

#endif // TEXTURE_H
