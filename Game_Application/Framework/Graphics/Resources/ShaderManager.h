//==============================================================================
// File        : ShaderManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// このクラスは、DirectX 11 における頂点シェーダー、ピクセルシェーダー、
// そして入力レイアウトを統合的に管理します。
// ファイルからコンパイル済みシェーダーを読み込み、対応する InputLayout を生成。
// SetShader() により描画時に一括設定を行い、SetTexture() でテクスチャも連携。
// シェーダーリソースをキャッシュして効率的に再利用できる構造となっています。
//==============================================================================
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <d3d11.h>
#include <wrl/client.h>
#include <string>
#include <unordered_map>
#include "MathTransform.h"
#include "ShaderTypes.h"

namespace Framework {

    class ShaderManager {
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context;

        std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11VertexShader>> m_VertexShaders;
        std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11PixelShader>>  m_PixelShaders;
        std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11InputLayout>>  m_InputLayouts;

        ShaderManager();
        ~ShaderManager();
        ShaderManager(const ShaderManager&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;

    public:
        static ShaderManager& GetInstance() {
            static ShaderManager instance;
            return instance;
        }

        bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
        void Finalize();

        void LoadVS(const std::wstring& name, const std::wstring& vsPath, Shader::VertexLayoutType layoutType = Shader::VertexLayoutType::Default);
        void LoadPS(const std::wstring& name, const std::wstring& psPath);
        bool LoadShaderFile(const std::wstring& path, std::vector<char>& outShaderData);

        void SetShader(const std::wstring& name);
        void SetTexture(UINT slot, ID3D11ShaderResourceView* texture);

    private:
        bool CreateInputLayoutByType(Shader::VertexLayoutType type, const void* vsData, size_t vsSize, ComPtr<ID3D11InputLayout>& layout);
    };
}

#endif // SHADER_MANAGER_H