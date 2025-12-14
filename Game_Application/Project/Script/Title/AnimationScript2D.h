//==============================================================================
// File        : AnimationScript2D.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-13
// Last Update : 2025-12-13
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef ANIMATION_SCRIPT_2D_H
#define ANIMATION_SCRIPT_2D_H

#include "GameBehaviour.h"
#include "Framework/Scene/Components/RenderComponent/SpriteComponent.h"

class AnimationScript2D : public Framework::GameBehaviour {
private:
	Framework::SpriteComponent* m_SpriteComponent = nullptr;
	math::vector3f m_BasePosition{};
	math::vector3f m_BaseScale{};

	// uv animation
	bool m_IsUV = false;
	float m_UVFrequency = 0.0f;
	int m_AtlasU = 1;
	int m_AtlasV = 1;

	// move animation
	bool m_IsMove = false;
	float m_MoveFrequency = 0.0f;
	float m_MoveSpeed = 1.0f;
	float m_MoveTime = 0.0f;
	float m_MoveRange = 5.0f;

	// scale animation
	bool m_IsScale = false;
	float m_ScaleFrequency = 0.0f;
	float m_ScaleSpeed = 1.0f;
	float m_ScaleTime = 0.0f;
	float m_ScaleRange = 5.0f;

	// color animation
	bool m_IsColor = false;
	float m_ColorFrequency = 0.0f;
	float m_ColorSpeed = 1.0f;
	float m_ColorTime = 0.0f;
	float m_ColorRangeMin = 0.0f;
	float m_ColorRangeMax = 1.0f;

public:
	void Start() override;
	void Update() override;

	void SetUV(int u, int v, float second = 0.0f) {
		m_IsUV = true;
		m_UVFrequency = second;
		m_AtlasU = u;
		m_AtlasV = v;
	}
	void SetMove(float speed, float range, float second = 0.0f) {
		m_IsMove = true;
		m_MoveFrequency = second;
		m_MoveSpeed = speed;
		m_MoveRange = range;
	}
	void SetScale(float speed, float range, float second = 0.0f) {
		m_IsScale = true;
		m_ScaleFrequency = second;
		m_ScaleSpeed = speed;
		m_ScaleRange = range;
	}
	void SetColor(float speed, float rangeMin = 0.0f, float rangeMax = 1.0f, float second = 0.0f) {
		m_IsColor = true;
		m_ColorFrequency = second;
		m_ColorSpeed = speed;
		m_ColorRangeMin = rangeMin;
		m_ColorRangeMax = rangeMax;
	}

private:
	void UVAnimation();
	void MoveAnimation();
	void ScaleAnimation();
	void ColorAnimation();
};

#endif // ANIMATION_SCRIPT_2D_H
