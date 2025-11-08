//==============================================================================
// File        : RenderTargetManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるレンダーターゲットとデプスステンシルを管理します。
// レンダーターゲットは描画の出力先となるテクスチャであり、
// デプスステンシルはオブジェクトの奥行きや描画マスクを管理します。
// Initialize() でバックバッファおよび深度バッファを作成し、
// Bind() で描画先として設定、Clear() で描画前に初期化します。
// Finalize() で作成したリソースを安全に解放します。
// このクラスにより、描画の基盤を安全かつ効率的に整えることができます。
//==============================================================================
#ifndef RENDER_TARGET_MANAGER_H
#define RENDER_TARGET_MANAGER_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class RenderTargetManager {
    private:
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
        Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilBuffer;

    public:
        RenderTargetManager();
        ~RenderTargetManager();

        bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, IDXGISwapChain* swapChain);
        void Finalize();

        void Clear(ID3D11DeviceContext* context, const float clearColor[4]);
        void Bind(ID3D11DeviceContext* context);

        ID3D11RenderTargetView* GetRenderTargetView() const { return m_RenderTargetView.Get(); }
        ID3D11DepthStencilView* GetDepthStencilView() const { return m_DepthStencilView.Get(); }
    };
}

#endif // RENDER_TARGET_MANAGER_H