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
#include "PlayerScript.h"
#include "GameObject.h"
#include "Components/PhysicsComponent/Rigidbody.h"
#include "Components/CameraComponent/TopDownCamera.h"
#include "InputKeyboard.h"
#include "Framework/Core/Timer.h"

using namespace Framework;

void PlayerScript::Start() {
    // Initialization code here
    
}

void PlayerScript::Update() {
    // Update code here
    auto rb = GetOwner()->GetComponent<Rigidbody>();
    auto cam = FindObject("MainCamera")->GetComponent<TopDownCamera>();

    if (rb) {
        // Example: Move right constantly
		InputKeyboard& keyboard = InputKeyboard::GetInstance();
        math::vector3f inputDir = math::zero<math::vector3f>();
		math::vector3f cameraForward = cam->GetForward();
		math::vector3f cameraBackward = cam->GetBackward();
		math::vector3f cameraLeft = cam->GetLeft();
		math::vector3f cameraRight = cam->GetRight();

		auto velocity = rb->GetVelocity();
		float speed = 3.0f;
		//float jumpForce = 75.0f;
        
        if (keyboard.IsKeyDown(KB::D)) {
            inputDir += cameraRight;
        }
        if (keyboard.IsKeyDown(KB::A)) {
            inputDir += cameraLeft;
        }
        if (keyboard.IsKeyDown(KB::W)) {
            inputDir += cameraForward;
        }
        if (keyboard.IsKeyDown(KB::S)) {
            inputDir += cameraBackward;
        }

        if (inputDir.lengthSquared() > 0) {
            velocity.x = math::normalize(inputDir).x * speed;
            velocity.z = math::normalize(inputDir).z * speed;
        }
        else {
            velocity.x = 0.0f;
			velocity.z = 0.0f;
        }
		rb->SetVelocity(velocity);

        //if (m_GroundContacts > 0) {
        //    m_IsGround = true;
        //    m_GroundTimer = m_GroundGraceTime;
        //}
        //else {
        //    m_GroundTimer -= Timer::GetInstance().GetDeltaTime();
        //    if (m_GroundTimer <= 0.0f) m_IsGround = false;
        //}

        //// ƒWƒƒƒ“ƒv
        //if (keyboard.IsKeyTriggered(KB::Space) && m_IsGround) {
        //    rb->AddForce(math::vector3f(0.0f, jumpForce, 0.0f));
        //}
	}
}

//void PlayerScript::OnTriggerEnter(Framework::GameObject* other) {
//    if (other->GetTag() == "Block") {
//        m_GroundContacts++;
//    }
//}
//
//void PlayerScript::OnTriggerExit(Framework::GameObject* other) {
//    if (other->GetTag() == "Block") {
//        m_GroundContacts--;
//    }
//}
