//==============================================================================
// File        : ConstantBuffer.inl
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef CONSTANT_BUFFER_MANAGER_INL
#define CONSTANT_BUFFER_MANAGER_INL

template<typename T>
inline void ConstantBufferManager::Update(ID3D11DeviceContext* context, const T& data, UINT slot, Shader::ShaderStage stage) {

    if (slot >= m_Buffer.size())
        m_Buffer.resize(slot + 1);

    if (!m_Buffer[slot]) {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.ByteWidth = sizeof(T);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = &data;

        HRESULT hr = m_Device->CreateBuffer(&desc, &initData, &m_Buffer[slot]);
        if (FAILED(hr)) { return; }
    }

    ID3D11Buffer* buffer = m_Buffer[slot].Get();
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    HRESULT hr = context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    if (SUCCEEDED(hr)) {
        memcpy(mapped.pData, &data, sizeof(T));
        context->Unmap(buffer, 0);
    }

    switch (stage) {
    case Shader::ShaderStage::Vertex:
        context->VSSetConstantBuffers(slot, 1, &buffer);
        break;
    case Shader::ShaderStage::Pixel:
        context->PSSetConstantBuffers(slot, 1, &buffer);
        break;
    }
}

#endif // CONSTANT_BUFFER_MANAGER_INL