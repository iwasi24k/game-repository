//==============================================================================
// File        : Mesh.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-12
// Last Update : 2025-11-12
//------------------------------------------------------------------------------
// Overview : ModelÇÃÉÅÉbÉVÉÖèÓïÒÇäiî[Ç∑ÇÈç\ë¢ëÃ
//==============================================================================
#ifndef MESH_H
#define MESH_H

#include <wrl/client.h>
#include <d3d11.h>
#include <memory>
#include <vector>

#include "Material.h"

namespace Framework {

    struct Mesh {
        Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
        UINT IndexCount = 0;
        Material MaterialData;

        void Draw(ID3D11DeviceContext* context);
    };
}

#endif // MESH_H