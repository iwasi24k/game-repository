//==============================================================================
// File        : Sprite.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-09
// Last Update : 2025-11-09
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Sprite.h"
#include "Renderer.h"
#include "ShaderManager.h"
#include "DebugTool.h"

using namespace Framework;

Sprite::Sprite() {}
Sprite::~Sprite() {}

bool Sprite::Initialize() {
	auto device = Renderer::GetInstance().GetDevice();

	// 動的バッファで初期作成
	D3D11_BUFFER_DESC vbDesc = {};
	vbDesc.ByteWidth = sizeof(Shader::SpriteVertex) * 4; // 4頂点
	vbDesc.Usage = D3D11_USAGE_DYNAMIC;
	vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	device->CreateBuffer(&vbDesc, nullptr, m_VertexBuffer.GetAddressOf());

	// インデックスバッファは静的でOK
	const uint16_t indices[] = { 0,1,2,1,3,2 };
	D3D11_BUFFER_DESC ibDesc = {};
	ibDesc.ByteWidth = sizeof(indices);
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA ibData = {};
	ibData.pSysMem = indices;
	device->CreateBuffer(&ibDesc, &ibData, m_IndexBuffer.GetAddressOf());

	m_Width = 1.0f;
	m_Height = 1.0f;
	m_UV = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_TransformMatrix = math::matrix::Identity();
	m_Color = { 1.0f,1.0f,1.0f,1.0f };
	UpdateVertexBuffer();

	LOG_IF(L"Sprite Initialize Completed");
	return true;
}

void Sprite::Finalize() {
	LOG_IF(L"Sprite Finalize..");

	m_Texture.reset();
	m_VertexBuffer.Reset();
	m_IndexBuffer.Reset();
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
	m_Texture = texture;
}

void Sprite::SetSize(float width, float height) {
	m_Width = width;
	m_Height = height;
	UpdateVertexBuffer();
}

void Sprite::SetUV(float u0, float v0, float u1, float v1) {
	m_UV = { u0, v0, u1, v1 };
	UpdateVertexBuffer();
}

void Sprite::SetTransform(const math::transform<math::vector2f>& transform) {
	math::transform<math::vector3f> trans({ transform.position.x, transform.position.y, 0.0f }, { transform.scale.x, transform.scale.y, 1.0f }, { 0.0f, 0.0f, transform.rotation });
	m_TransformMatrix = trans.toMatrix();
}
void Sprite::SetTransform(const math::vector2f& position, const math::vector2f& scale, float rotation) {
	math::transform<math::vector3f> transform({ position.x, position.y, 0.0f }, { scale.x, scale.y, 1.0f }, { 0.0f, 0.0f, rotation });
	m_TransformMatrix = transform.toMatrix();
}

void Sprite::SetColor(const math::vector4f& color) {
	m_Color = color;
}

void Sprite::Draw() {
	if (!m_Texture || !m_Texture->GetSRV()) return;

	auto& renderer = Renderer::GetInstance();
	auto& shader = ShaderManager::GetInstance();

	math::matrix view = math::matrix::Identity();
	math::matrix proj = math::matrix::OrthographicOffCenterLH(0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 1);

	renderer.SetMatrix(m_TransformMatrix.Transposed(), view, proj.Transposed());
	renderer.SetColor(m_Color);

	UINT stride = sizeof(Shader::SpriteVertex);
	UINT offset = 0;
	renderer.GetContext()->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	renderer.GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	renderer.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader.SetTexture(0, m_Texture->GetSRV());

	renderer.GetContext()->DrawIndexed(6, 0, 0);
}


void Sprite::CreateVertexBuffer(ID3D11Device* device) {
	// 初期サイズに基づくバッファを作成
	UpdateVertexBuffer();
}

void Sprite::UpdateVertexBuffer() {
	auto deviceContext = Renderer::GetInstance().GetContext();

	D3D11_MAPPED_SUBRESOURCE mapped = {};
	deviceContext->Map(m_VertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

	Shader::SpriteVertex* verts = reinterpret_cast<Shader::SpriteVertex*>(mapped.pData);
	verts[0] = { {-0.5f * m_Width,-0.5f * m_Height},{m_UV.u0,m_UV.v0} }; // 左上
	verts[1] = { { 0.5f * m_Width,-0.5f * m_Height},{m_UV.u1,m_UV.v0} }; // 右上
	verts[2] = { {-0.5f * m_Width, 0.5f * m_Height},{m_UV.u0,m_UV.v1} }; // 左下
	verts[3] = { { 0.5f * m_Width, 0.5f * m_Height},{m_UV.u1,m_UV.v1} }; // 右下

	deviceContext->Unmap(m_VertexBuffer.Get(), 0);
}