//==============================================================================
// File        : SwapChain.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 における SwapChain（スワップチェイン）を管理します。
// SwapChain とは、裏画面と表画面のバッファを入れ替えながら描画を行い、
// 画面のちらつきを防ぎスムーズに描画するための仕組みです。
// Initialize() でスワップチェインを作成し、Present() で描画内容を画面に表示します。
// Finalize() でスワップチェインを解放し、リソースを安全に片付けます。
//==============================================================================
#ifndef SWAP_CHAIN_H
#define SWAP_CHAIN_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class SwapChain {
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;

    public:
        SwapChain();
        ~SwapChain();

        bool Initialize(HWND hWnd, ID3D11Device* device);
        void Finalize();

        void Present();

        IDXGISwapChain* GetSwapChain() const { return m_SwapChain.Get(); }
    };
}

#endif // SWAP_CHAIN_H