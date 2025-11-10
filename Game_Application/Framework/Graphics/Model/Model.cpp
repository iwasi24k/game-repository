#include "pch.h"
#include "Model.h"
#include <Assimp/Include/Importer.hpp>
#include <Assimp/Include/postprocess.h>
#include <string>

using namespace Framework;

// ヘルパー：wstring -> UTF8
//static std::string WStringToUTF8(const std::wstring& ws) {
//    return std::string(ws.begin(), ws.end()); // 環境によりより正確な変換を使ってください
//}
//
//bool Model::Initialize(const std::wstring& filePath) {
//    std::wstring modelPath = L"Asset\\Model\\" + filePath;
//    std::string narrowPath = WStringToUTF8(modelPath);
//
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(narrowPath,
//        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//    if (!scene || !scene->HasMeshes()) return false;
//
//    m_TexManager = std::make_shared<TextureManager>();
//
//    m_Meshes.clear();
//    LoadMeshesFromScene(scene);
//
//    m_TransformMatrix = math::matrix::Identity();
//    return true;
//}
//
//void Model::Finalize()
//{
//    m_Meshes.clear();
//    m_Texture.reset();
//    m_TexManager.reset();
//}
//
//void Model::LoadMeshesFromScene(const aiScene* scene)
//{
//    auto device = ServiceLocator::Get<Renderer>()->GetDevice();
//
//    // モデルディレクトリの取得（テクスチャ相対パス解決用）
//    // TODO: 実パス抽出処理が必要であれば実装
//
//    for (UINT i = 0; i < scene->mNumMeshes; ++i)
//    {
//        const aiMesh* ai_mesh = scene->mMeshes[i];
//
//        std::vector<Shader::Vertex> vertices(ai_mesh->mNumVertices);
//        for (UINT v = 0; v < ai_mesh->mNumVertices; ++v)
//        {
//            Shader::Vertex& vert = vertices[v];
//            vert.Position = { ai_mesh->mVertices[v].x, ai_mesh->mVertices[v].y, ai_mesh->mVertices[v].z };
//            vert.Normal = ai_mesh->HasNormals() ? math::vector3f{ ai_mesh->mNormals[v].x, ai_mesh->mNormals[v].y, ai_mesh->mNormals[v].z } : math::vector3f{};
//            vert.TexCoord = ai_mesh->HasTextureCoords(0) ? math::vector2f{ ai_mesh->mTextureCoords[0][v].x, ai_mesh->mTextureCoords[0][v].y } : math::vector2f{};
//            vert.VertexColor = math::vector4f{ 1,1,1,1 };
//        }
//
//        std::vector<UINT> indices;
//        for (UINT f = 0; f < ai_mesh->mNumFaces; ++f)
//        {
//            const aiFace& face = ai_mesh->mFaces[f];
//            indices.insert(indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
//        }
//
//        auto mesh = std::make_shared<Mesh>();
//        if (!mesh->Initialize(device, vertices, indices))
//        {
//            // バッファ作成失敗時はスキップするかログを出す
//            continue;
//        }
//
//        // マテリアル設定
//        if (ai_mesh->mMaterialIndex >= 0)
//        {
//            const aiMaterial* aiMat = scene->mMaterials[ai_mesh->mMaterialIndex];
//            auto mat = LoadMaterialFromAi(aiMat, scene);
//            mesh->SetMaterial(mat);
//        }
//
//        m_Meshes.push_back(mesh);
//    }
//}
//
//std::shared_ptr<Material> Model::LoadMaterialFromAi(const aiMaterial* material, const aiScene* scene)
//{
//    auto mat = std::make_shared<Material>();
//
//    aiColor4D color;
//    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color))
//        mat->Diffuse = { color.r, color.g, color.b, color.a };
//    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color))
//        mat->Ambient = { color.r, color.g, color.b, color.a };
//    if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color))
//        mat->Specular = { color.r, color.g, color.b, color.a };
//    float shininess;
//    if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess))
//        mat->Shininess = shininess;
//
//    aiString texPath;
//    if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
//    {
//        std::string texName = texPath.C_Str();
//
//        int embeddedIndex = -1;
//        for (unsigned int i = 0; i < scene->mNumTextures; ++i)
//        {
//            if (scene->mTextures[i] && scene->mTextures[i]->mFilename.C_Str() == texName)
//            {
//                embeddedIndex = static_cast<int>(i);
//                break;
//            }
//        }
//
//        if (embeddedIndex >= 0)
//        {
//            const aiTexture* embeddedTex = scene->mTextures[embeddedIndex];
//            // 埋め込みテクスチャ：Assimpのフォーマットに応じた処理が必要
//            // ここでは簡易にメモリからロードする想定の API を呼びます（既存の TextureManager を利用）
//            mat->TexturePtr = m_TexManager->LoadFromMemory(
//                reinterpret_cast<unsigned char*>(embeddedTex->pcData),
//                embeddedTex->mWidth
//            );
//        }
//        else
//        {
//            // 外部テクスチャの相対パス解決（モデルDir + texName）を入れるべき
//            std::wstring wpath(texName.begin(), texName.end());
//            mat->TexturePtr = m_TexManager->LoadTexture(L"Asset\\Texture\\" + wpath);
//        }
//    }
//
//    return mat;
//}
//
//void Model::Draw(const math::matrix& view, const math::matrix& projection)
//{
//    auto renderer = ServiceLocator::Get<Renderer>();
//    auto context = renderer->GetContext();
//
//    renderer->SetMatrix(m_TransformMatrix.Transposed(), view.Transposed(), projection.Transposed());
//    renderer->SetLight({ 1,1,1,1 });
//
//    for (auto& mesh : m_Meshes)
//    {
//        // メッシュ毎のテクスチャ優先、無ければモデル全体のテクスチャ
//        auto mat = mesh->GetMaterial();
//        if (mat && mat->TexturePtr)
//            renderer->SetMaterial( /*...*/); // 既存 SetMaterial 呼び出しにマテリアルの値を渡す
//        else
//            renderer->SetMaterial(/*... fallback ...*/);
//
//        // PSSetShaderResources や SetColor は renderer 経由でやる（既存の呼び出しをそのまま使ってください）
//        // ここでは mesh->Draw だけ呼ぶ
//        mesh->Draw(context);
//    }
//}
