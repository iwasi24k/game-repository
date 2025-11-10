//==============================================================================
// File        : Model.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-10
// Last Update : 2025-11-10
//------------------------------------------------------------------------------
// Overview :
//==============================================================================
#ifndef MODEL_H
#define MODEL_H

#include <Assimp/Include/scene.h>

#include <vector>
#include <memory>
#include <string>

#include "Mesh.h"
#include "Material.h"
#include "TextureManager.h"
/*
namespace Framework {

    class Model {
    private:
        std::vector<std::shared_ptr<Mesh>> m_Meshes;
        std::shared_ptr<TextureManager> m_TexManager;

        math::transform<math::vector3f> m_Transform;

    public:
        Model() = default;
        ~Model() = default;

        bool Initialize(const std::wstring& filePath);
        void Finalize();

        void SetTransform(const math::vector3f& position,
            const math::vector3f& scale,
            const math::vector3f& rotation);

        void Draw(const math::matrix& view, const math::matrix& projection);

    private:
        void LoadMeshesFromScene(const aiScene* scene);
        std::shared_ptr<Material> LoadMaterialFromAi(const aiMaterial* material, const aiScene* scene);
    };
}*/

#endif // MODEL_H