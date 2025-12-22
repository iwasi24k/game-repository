//==============================================================================
// File        : PlayerSkillScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-22
// Last Update : 2025-12-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef PLAYER_SKILL_SCRIPT_H
#define PLAYER_SKILL_SCRIPT_H

#include "GameBehaviour.h"
#include "GameObject.h"

class PlayerSkillScript : public Framework::GameBehaviour {
private:
	enum class PlayerSkillState { Idle, Action };

	PlayerSkillState m_SkillState = PlayerSkillState::Idle;
	Framework::GameObject* m_GameObject = nullptr;

	bool m_IsActivation = false;
	bool m_IsAction = false;

	static constexpr float kActionSpeed = 4.0f;
	static constexpr float kActionMaxScale = 7.0f;

	static constexpr math::vector4f kDefaultColor = { 0.5f, 0.5f, 0.5f, 1.0f };

	static constexpr float kMaxCoolTime = 2.5f;
	float m_CoolTime = 0.0f;

public:
	void Start() override;
	void Update() override;

	void SkillActivation();

	void OnTriggerEnter(Framework::GameObject* other) override;

private:
	void PlayerActionAnimation();
};

#endif // PLAYER_SKILL_SCRIPT_H