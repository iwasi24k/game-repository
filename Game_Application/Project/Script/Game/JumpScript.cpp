//==============================================================================
// File        : PlayerScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "JumpScript.h"
#include "GameObject.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/CameraComponent/TopDownCamera.h"
#include "InputKeyboard.h"
#include "Framework/Core/Timer.h"

using namespace Framework;

void JumpScript::Start() {
    // Initialization code here

}

void JumpScript::Update() {
    // Update code here
    auto rb = GetOwner()->GetComponent<Rigidbody>();

    if (!rb) return;
    InputKeyboard& keyboard = InputKeyboard::GetInstance();

    float jumpForce = 75.0f;

    if (m_GroundContacts > 0) {
        m_IsGround = true;
        m_GroundTimer = m_GroundGraceTime;
    }
    else {
        m_GroundTimer -= Timer::GetInstance().GetDeltaTime();
        if (m_GroundTimer <= 0.0f) m_IsGround = false;
    }

    m_Frame++;
    if (m_Frame > m_CoolTime) {

        if (keyboard.IsKeyTriggered(KB::Space) && m_IsGround) {
            rb->AddForce(math::vector3f(0.0f, jumpForce, 0.0f));
            m_Frame = 0.0f;
        }
    }
}

void JumpScript::OnTriggerEnter(Framework::GameObject* other) {
    if (other->GetTag() == "Block") {
        m_GroundContacts++;
    }
}

void JumpScript::OnTriggerExit(Framework::GameObject* other) {
    if (other->GetTag() == "Block") {
        m_GroundContacts--;
    }
}
