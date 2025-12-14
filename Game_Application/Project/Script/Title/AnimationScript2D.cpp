//==============================================================================
// File        : AnimationScript2D.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-13
// Last Update : 2025-12-13
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "AnimationScript2D.h"
#include "GameObject.h"
#include "MathTransform.h"
#include "Timer.h"

using namespace Framework;

void AnimationScript2D::Start() {
	m_SpriteComponent = GetOwner()->GetComponent<SpriteComponent>();
	m_BasePosition = GetOwner()->GetTransform().position;
	m_BaseScale = GetOwner()->GetTransform().scale;
}

void AnimationScript2D::Update() {

	UVAnimation();
	MoveAnimation();
	ScaleAnimation();
	ColorAnimation();
}

void AnimationScript2D::UVAnimation() {
	if (!m_IsUV) return;

	static float frame = 0.0f;
	if (frame < m_UVFrequency) {
		frame += Timer::GetInstance().GetDeltaTime();
		return;
	}
	frame = 0.0f;

	static float UV_W = 1.0f / m_AtlasU;
	static float UV_H = 1.0f / m_AtlasV;

	static int index = 0; // 0 ~ 15

	int x = index % m_AtlasU;
	int y = index / m_AtlasV;

	float u0 = x * UV_W;
	float v0 = y * UV_H;
	float u1 = u0 + UV_W;
	float v1 = v0 + UV_H;

	m_SpriteComponent->SetUV(u0, v0, u1, v1);
	index = (index + 1) % (m_AtlasU * m_AtlasV);
}

void AnimationScript2D::MoveAnimation() {
	if (!m_IsMove) return;

	static float frame = 0.0f;
	if (frame < m_MoveFrequency) {
		frame += Timer::GetInstance().GetDeltaTime();
		return;
	}
	frame = 0.0f;

	// 座標をゆらゆら移動させたい。（ループ）
	static float waveTime = 0.0f;
	waveTime += Timer::GetInstance().GetDeltaTime();

	// ③ ゆらゆら計算
	float offset = std::sin(waveTime * m_MoveSpeed) * m_MoveRange;

	auto& pos = GetOwner()->GetTransform().position;
	pos.y = m_BasePosition.y + offset;
}

void AnimationScript2D::ScaleAnimation() {
	if (!m_IsScale) return;

	// 更新頻度制御
	static float frame = 0.0f;
	if (frame < m_ScaleFrequency) {
		frame += Timer::GetInstance().GetDeltaTime();
		return;
	}
	frame = 0.0f;

	// 揺れ用時間
	static float waveTime = 0.0f;
	waveTime += Timer::GetInstance().GetDeltaTime();

	// スケールゆらゆら計算
	float offset = std::sin(waveTime * m_ScaleSpeed) * m_ScaleRange;

	auto& scale = GetOwner()->GetTransform().scale;
	scale.x = m_BaseScale.x + offset;
	scale.y = m_BaseScale.y + offset;
}

void AnimationScript2D::ColorAnimation() {
	if (!m_IsColor) return;

	// 更新頻度制御
	static float frame = 0.0f;
	if (frame < m_ColorFrequency) {
		frame += Timer::GetInstance().GetDeltaTime();
		return;
	}
	frame = 0.0f;

	// 揺れ用時間
	static float waveTime = 0.0f;
	waveTime += Timer::GetInstance().GetDeltaTime();

	// sin を 0～1 に正規化
	float s = (std::sin(waveTime * m_ColorSpeed) + 1.0f) * 0.5f;

	// レンジにマッピング（clamp 不要）
	float alpha =
		m_ColorRangeMin +
		s * (m_ColorRangeMax - m_ColorRangeMin);

	m_SpriteComponent->SetColor({1.0f, 1.0f, 1.0f, alpha });
}

