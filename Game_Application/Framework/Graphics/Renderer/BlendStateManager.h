//==============================================================================
// File        : BlendStateManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 におけるブレンドステートを管理します。
// ブレンドステートは描画結果をフレームバッファに合成する際のルールを定義します。
// Initialize() で標準アルファブレンディングと AlphaToCoverage 用のステートを作成し、
// Apply() で描画時にどちらのステートを使用するか切り替えます。
// Finalize() で作成したステートを解放し、GPU リソースを安全に管理します。
// このクラスにより、半透明オブジェクトやエフェクトの描画を柔軟に制御できます。
//==============================================================================
#ifndef BLEND_STATE_MANAGER_H
#define BLEND_STATE_MANAGER_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class BlendStateManager {
    private:
        Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState;
        Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendStateATC;

    public:
        BlendStateManager();
        ~BlendStateManager();

        bool Initialize(ID3D11Device* device);
        void Finalize();

        void Apply(ID3D11DeviceContext* context, bool useAlphaToCoverage = false);
    };
}

#endif // BLEND_STATE_MANAGER_H