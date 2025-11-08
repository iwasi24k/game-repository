//==============================================================================
// File        : RasterizerStateManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるラスタライザーステートを管理します。
// ラスタライザーは、3D モデルの頂点を画面上のピクセルに変換する際の設定を司ります。
// Initialize() でカリング有効／無効のステートを作成し、
// Apply() で描画時にどちらのステートを適用するか切り替えます。
// Finalize() で作成したステートを安全に解放します。
// このクラスにより、描画の裏面カリングを簡単かつ安全に制御できます。
//==============================================================================
#ifndef RASTERIZER_STATE_MANAGER_H
#define RASTERIZER_STATE_MANAGER_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class RasterizerStateManager {
    private:
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullOnState;
        Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_CullOffState;

    public:
        RasterizerStateManager();
        ~RasterizerStateManager();

        bool Initialize(ID3D11Device* device);
        void Finalize();

        void Apply(ID3D11DeviceContext* context, bool enable);
    };
}

#endif // RASTERIZER_STATE_MANAGER_H