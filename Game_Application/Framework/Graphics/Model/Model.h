//==============================================================================
// File        : Model.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-12
// Last Update : 2025-11-12
//------------------------------------------------------------------------------
// Overview :
// このクラスは、Assimp で読み込んだ 3D モデルを管理します。
// Initialize() によりファイルから頂点・インデックス・マテリアルを読み込み、
// Mesh 単位で頂点バッファ・インデックスバッファを生成します。
// マテリアル情報（Diffuse, Ambient, Specular, Emission, Shininess）やテクスチャも管理。
// SetTransform() でワールド変換を設定でき、Draw() で各メッシュを Renderer と ShaderManager を介して描画。
// 外部テクスチャと埋め込みテクスチャの両方に対応し、複数メッシュを効率的に扱える構造です。
//==============================================================================
#ifndef MODEL_H
#define MODEL_H

#include "Renderer.h"
#include <vector>
#include <Assimp/Include/scene.h>

#include "ShaderTypes.h"
#include "TextureManager.h"
#include "Mesh.h"

namespace Framework {

    class Model {
    public:
        Model();
        ~Model();

        bool Initialize(const std::wstring& path);
        void Finalize();

        void SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation);
        void SetAlpha(float alpha) { m_Alpha = alpha; }
        void SetOverrideMaterial(const Material& material);
        void SetOverrideTexture(UINT slot, const std::wstring& texturePath);

        void Draw(const math::matrix& view, const math::matrix& proj);

    private:
        std::vector<Mesh> m_Meshes;
        math::transform<math::vector3f> m_Transform;
        math::matrix m_TransformMatrix = math::matrix::Identity();
        float m_Alpha = 1.0f;

        void LoadMeshesFromScene(const aiScene* scene);
        void LoadMaterial(const aiMaterial* material, const aiScene* scene, Mesh& mesh);

        void CreateVertexBuffer(ID3D11Device* device, const std::vector<Shader::Vertex>& vertices, Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer);
        void CreateIndexBuffer(ID3D11Device* device, const std::vector<UINT>& indices, Microsoft::WRL::ComPtr<ID3D11Buffer>& buffer);
    };

} // namespace Framework


#endif // MODEL_H