//==============================================================================
// File        : Model.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-12
// Last Update : 2025-11-12
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Model.h"
#include <Assimp/Include/Importer.hpp>
#include <Assimp/Include/postprocess.h>

#include "Renderer.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "DebugTool.h"

using namespace Framework;

Model::Model() {}
Model::~Model() {}

bool Model::Initialize(const std::wstring& filePath) {
    std::string narrowPath(filePath.begin(), filePath.end());

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(narrowPath,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || !scene->HasMeshes()) return false;

    m_Meshes.clear();
    LoadMeshesFromScene(scene);

    m_TransformMatrix = math::matrix::Identity();
    return true;
}

void Model::Finalize() {
    m_Meshes.clear();
}

void Model::SetTransform(const math::vector3f& position, const math::vector3f& scale, const math::vector3f& rotation) {
    m_Transform = { position, scale, rotation };
    m_TransformMatrix = m_Transform.toMatrix();
}

void Model::Draw(const math::matrix& view, const math::matrix& proj) {
    auto renderer = &Renderer::GetInstance();
    auto context = renderer->GetContext();

    for (auto& mesh : m_Meshes) {
        renderer->SetMatrix(m_TransformMatrix.Transposed(), view.Transposed(), proj.Transposed());

        // Material設定
        renderer->SetMaterial(
            mesh.MaterialData.Diffuse,        // Diffuse
            mesh.MaterialData.Ambient,        // Ambient
            mesh.MaterialData.Specular,       // Specular
            mesh.MaterialData.Emission,       // Emission
            mesh.MaterialData.Shininess,      // Shininess
            mesh.MaterialData.Texture != nullptr // TextureEnable
        );


        if (mesh.MaterialData.Texture)
            ShaderManager::GetInstance().SetTexture(0, mesh.MaterialData.Texture->GetSRV());

        mesh.Draw(context);
        context->DrawIndexed(mesh.IndexCount, 0, 0);
    }
}

// --- プライベート関数 ---
void Model::LoadMeshesFromScene(const aiScene* scene) {
    auto device = Renderer::GetInstance().GetDevice();

    for (UINT i = 0; i < scene->mNumMeshes; ++i) {
        const aiMesh* ai_mesh = scene->mMeshes[i];
        Mesh mesh;

        // 頂点
        std::vector<Shader::Vertex> vertices(ai_mesh->mNumVertices);
        for (UINT v = 0; v < ai_mesh->mNumVertices; ++v) {
            Shader::Vertex& vert = vertices[v];
            vert.Position = { ai_mesh->mVertices[v].x, ai_mesh->mVertices[v].y, ai_mesh->mVertices[v].z };
            vert.Normal = ai_mesh->HasNormals() ? math::vector3f{ ai_mesh->mNormals[v].x, ai_mesh->mNormals[v].y, ai_mesh->mNormals[v].z } : math::vector3f{};
            vert.TexCoord = ai_mesh->HasTextureCoords(0) ? math::vector2f{ ai_mesh->mTextureCoords[0][v].x, ai_mesh->mTextureCoords[0][v].y } : math::vector2f{};
            vert.Diffuse = { 1,1,1,1 };
        }

        // インデックス
        std::vector<UINT> indices;
        for (UINT f = 0; f < ai_mesh->mNumFaces; ++f) {
            const aiFace& face = ai_mesh->mFaces[f];
            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }
        mesh.IndexCount = static_cast<UINT>(indices.size());

        CreateVertexBuffer(device, vertices, mesh.VertexBuffer);
        CreateIndexBuffer(device, indices, mesh.IndexBuffer);

        // マテリアル
        if (ai_mesh->mMaterialIndex >= 0)
            LoadMaterial(scene->mMaterials[ai_mesh->mMaterialIndex], scene, mesh);

        m_Meshes.push_back(std::move(mesh));
    }
}

void Model::LoadMaterial(const aiMaterial* material, const aiScene* scene, Mesh& mesh) {
    aiColor4D color;
    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
        mesh.MaterialData.Diffuse = math::vector4f{ color.r, color.g, color.b, color.a };

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color))
        mesh.MaterialData.Ambient = math::vector4f{ color.r, color.g, color.b, color.a };

    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color))
        mesh.MaterialData.Specular = math::vector4f{ color.r, color.g, color.b, color.a };

	if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color))
		mesh.MaterialData.Emission = math::vector4f{ color.r, color.g, color.b, color.a };

    float shininess;
    if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess))
        mesh.MaterialData.Shininess = shininess;

    aiString texPath;
    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS) {
        std::string texName = texPath.C_Str();

        int embeddedIndex = -1;
        for (unsigned int i = 0; i < scene->mNumTextures; ++i) {
            std::string embeddedName = scene->mTextures[i]->mFilename.C_Str();
            if (embeddedName == texName) {
                embeddedIndex = i;
                break;
            }
        }

        if (embeddedIndex >= 0) {
            // 埋め込みテクスチャの処理
            const aiTexture* embeddedTex = scene->mTextures[embeddedIndex];
            mesh.MaterialData.Texture = TextureManager::GetInstance().LoadFromMemory(
                reinterpret_cast<unsigned char*>(embeddedTex->pcData),
                embeddedTex->mWidth
            );
        }
        else {
            // 外部テクスチャの処理
            mesh.MaterialData.Texture = TextureManager::GetInstance().LoadTexture(/*L"Asset\\Texture\\" + */std::wstring(texName.begin(), texName.end()));
        }
    }
}

void Model::CreateVertexBuffer(ID3D11Device* device, const std::vector<Shader::Vertex>& vertices, ComPtr<ID3D11Buffer>& buffer) {
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(Shader::Vertex) * static_cast<UINT>(vertices.size());
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = vertices.data();

    device->CreateBuffer(&desc, &initData, buffer.GetAddressOf());
}

void Model::CreateIndexBuffer(ID3D11Device* device, const std::vector<UINT>& indices, ComPtr<ID3D11Buffer>& buffer) {
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(UINT) * static_cast<UINT>(indices.size());
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = indices.data();

    device->CreateBuffer(&desc, &initData, buffer.GetAddressOf());
}