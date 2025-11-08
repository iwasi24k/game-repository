//==============================================================================
// File        : ViewportManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるビューポート（Viewport）を管理します。
// ビューポートは描画する領域の位置とサイズ、そして深度範囲を定義する設定です。
// Initialize() で画面サイズや深度範囲を設定し、Bind() で GPU に適用します。
// Finalize() は特にリソースを持たないため空実装です。
// このクラスにより、描画の範囲や奥行きの管理を簡単かつ安全に行うことができます。
//==============================================================================
#ifndef VIEWPORT_MANAGER_H
#define VIEWPORT_MANAGER_H

#include <d3d11.h>

namespace Framework {

	class ViewportManager {
	private:
		D3D11_VIEWPORT m_Viewport{};

	public:
		ViewportManager();
		~ViewportManager();

		bool Initialize();
		void Finalize();

		void Bind(ID3D11DeviceContext* context);
	};
}

#endif // VIEWPORT_MANAGER_H