//==============================================================================
// File        : ConstantBuffer.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 における定数バッファ（Constant Buffer）を管理します。
// 定数バッファはシェーダーに渡す描画パラメータ（行列、ライト情報、各種フラグなど）を格納するための GPU バッファです。
// Update() でデータをバッファに書き込み、指定スロットにバインドしてシェーダーに反映します。
// バッファが存在しない場合は動的バッファとして作成し、Finalize() で解放します。
// このクラスにより、シェーダーへのデータ転送を効率的かつ安全に管理できます。
//==============================================================================
#ifndef CONSTANT_BUFFER_MANAGER_H
#define CONSTANT_BUFFER_MANAGER_H

#include <vector>
#include <wrl/client.h>
#include <d3d11.h>

#include "ShaderManager.h"

namespace Framework {

    class ConstantBufferManager {
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
        std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> m_Buffer;

    public:
        ConstantBufferManager();
        ~ConstantBufferManager();

        bool Initialize(ID3D11Device* device);
        void Finalize();

        template<typename T>
        void Update(ID3D11DeviceContext* context, const T& data, UINT slot, Shader::ShaderStage stage);       
    };
}
#include "ConstantBufferManager.inl"

#endif // CONSTANT_BUFFER_MANAGER_H
