#include "pch.h"
#include "Mesh.h"
#include <stdexcept>

using namespace Framework;

bool Mesh::Initialize(ID3D11Device* device,
    const std::vector<Shader::Vertex>& vertices,
    const std::vector<UINT>& indices) {
    if (!device || vertices.empty() || indices.empty()) return false;

    // Vertex buffer
    D3D11_BUFFER_DESC vbd{};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = static_cast<UINT>(sizeof(Shader::Vertex) * vertices.size());
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinit{};
    vinit.pSysMem = vertices.data();

    if (FAILED(device->CreateBuffer(&vbd, &vinit, m_VertexBuffer.GetAddressOf())))
        return false;

    // Index buffer
    D3D11_BUFFER_DESC ibd{};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinit{};
    iinit.pSysMem = indices.data();

    if (FAILED(device->CreateBuffer(&ibd, &iinit, m_IndexBuffer.GetAddressOf())))
        return false;

    m_IndexCount = static_cast<UINT>(indices.size());
    return true;
}

void Mesh::Draw(ID3D11DeviceContext* context) {
    if (!context || !m_IndexCount) return;

    UINT stride = sizeof(Shader::Vertex);
    UINT offset = 0;
    ID3D11Buffer* vb = m_VertexBuffer.Get();
    context->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
    context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    context->DrawIndexed(m_IndexCount, 0, 0);
}

void Mesh::DrawInstanced(ID3D11DeviceContext* context, ID3D11Buffer* instanceBuffer, UINT instanceCount) {
    if (!context || !instanceCount || !m_IndexCount) return;

    ID3D11Buffer* buffers[2] = { m_VertexBuffer.Get(), instanceBuffer };
    UINT strides[2] = { sizeof(Shader::Vertex), sizeof(Shader::InstanceData) };
    UINT offsets[2] = { 0, 0 };
    context->IASetVertexBuffers(0, 2, buffers, strides, offsets);
    context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    context->DrawIndexedInstanced(m_IndexCount, instanceCount, 0, 0, 0);
}
