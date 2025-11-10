//==============================================================================
// File        : Mesh.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-10
// Last Update : 2025-11-10
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef MESH_H
#define MESH_H

#include <wrl/client.h>
#include <d3d11.h>
#include <memory>
#include <vector>

#include "Material.h"
#include "ShaderTypes.h"

namespace Framework {

    class Mesh {
    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
        UINT m_IndexCount = 0;

        std::shared_ptr<Material> m_Material;

    public:
        Mesh() = default;
        ~Mesh() = default;

        bool Initialize(ID3D11Device* device,
            const std::vector<Shader::Vertex>& vertices,
            const std::vector<UINT>& indices);

        void Draw(ID3D11DeviceContext* context);
        void DrawInstanced(ID3D11DeviceContext* context, ID3D11Buffer* instanceBuffer, UINT instanceCount);

        void SetMaterial(std::shared_ptr<Material> mat) { m_Material = mat; }
        std::shared_ptr<Material> GetMaterial() const { return m_Material; }

        UINT GetIndexCount() const { return m_IndexCount; }
    };
}

#endif // MESH_H