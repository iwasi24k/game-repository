//==============================================================================
// File        : BlockScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-30
// Last Update : 2025-11-30
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef BLOCK_SCRIPT_H
#define BLOCK_SCRIPT_H

#include "MonoBehaviour.h"
#include "Material.h"

enum class BlockState { Idle, Warning, Moving };

class BlockScript : public Framework::MonoBehaviour {
private:
	BlockState m_State = BlockState::Idle;

	float m_CurrentY = 0.0f;
    float m_TargetY = 0.0f;
	float m_MoveSpeed = 2.0f;

	const float m_WarningTime = 2.0f;
    float m_WarningTimer = 0.0f;

	Framework::Material m_Material = {};
	math::vector4f m_DefaultColor = math::vector4f(1.0f, 0.3f, 0.3f, 1.0f);
	math::vector4f m_WarningColor = math::vector4f(0.9f, 0.4f, 0.4f, 1.0f);

public:
    void Start() override;
    void Update() override;

	void SetMaterial(const Framework::Material& color) {
		m_Material = color;
	}

	void StartWarning(float targetY) {
		m_TargetY = targetY;
		m_State = BlockState::Warning;
		m_WarningTimer = 0.0f;
	}

	BlockState IsMoving() const {
		return m_State;
	}
};

#endif // BLOCK_SCRIPT_H