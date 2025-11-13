//==============================================================================
// File        : Mesh.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-12
// Last Update : 2025-11-12
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Mesh.h"
#include "ShaderTypes.h"
#include <stdexcept>

using namespace Framework;

void Mesh::Draw(ID3D11DeviceContext* context) {
    UINT stride = sizeof(Shader::Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}