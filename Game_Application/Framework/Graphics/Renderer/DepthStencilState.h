//==============================================================================
// File        : DepthStencilState.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 における深度ステンシルステートを管理します。
// 深度ステンシルステートは、オブジェクトの手前・奥の判定（深度テスト）や
// ステンシルテストの有効・無効、書き込み可否を設定する仕組みです。
// Initialize() で深度テスト有効／無効や書き込み制御のステートを作成し、
// Bind() や WriteBind() で描画時に適用します。
// Finalize() で作成したステートを解放し、GPU リソースを安全に管理します。
// このクラスにより、描画の奥行き制御や透明オブジェクトの描画を柔軟に制御できます。
//==============================================================================
#ifndef DEPTH_STENCIL_STATE_H
#define DEPTH_STENCIL_STATE_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class DepthStencilState {
    public:
        enum class Mode { EnableWrite, EnableNoWrite, Disable };

    private:
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthEnabledState;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthDisabledState;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthEnabledNoWriteState;

    public:
        DepthStencilState();
        ~DepthStencilState();

        bool Initialize(ID3D11Device* device);
        void Finalize();

        void Bind(ID3D11DeviceContext* context, bool enable);
        void WriteBind(ID3D11DeviceContext* context, bool enable);
    };
}

#endif // DEPTH_STENCIL_STATE_H