//==============================================================================
// File        : Device.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは DirectX 11 における描画デバイス（ID3D11Device）と
// デバイスコンテキスト（ID3D11DeviceContext）を管理します。
// デバイスは GPU への命令発行を担当し、コンテキストは描画指示を記録します。
// Initialize() でデバイスとコンテキストを作成し、
// Finalize() でリソースを安全に解放します。
// このクラスを通じて、描画処理の基盤を安全かつ効率的に扱うことができます。
//==============================================================================
#ifndef DEVICE_H
#define DEVICE_H

#include <d3d11.h>
#include <wrl/client.h>

namespace Framework {

    class Device {
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;

    public:
        Device();
        ~Device();

        bool Initialize();
        void Finalize();

        ID3D11Device* GetDevice() const { return m_Device.Get(); }
        ID3D11DeviceContext* GetContext() const { return m_Context.Get(); }
    };
}

#endif // DEVICE_H