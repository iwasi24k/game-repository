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
#include "InputKeyboard.h"

using namespace Framework;

void PlayerScript::Start() {
    // Initialization code here
    
}

void PlayerScript::Update() {
    // Update code here
    auto rb = GetOwner()->GetComponent<Rigidbody>();

    if (rb) {
        // Example: Move right constantly
		InputKeyboard& keyboard = InputKeyboard::GetInstance();
        math::vector3f inputDir = math::zero<math::vector3f>();
		math::vector3f cameraForward = math::vector3f(0.0f, 0.0f, 1.0f);
		math::vector3f cameraRight = math::vector3f(1.0f, 0.0f, 0.0f);

		auto velocity = rb->GetVelocity();
		float speed = 5.0f;
		float jumpForce = 5.0f;
        
        if (keyboard.IsKeyDown(KB::D)) {
            inputDir += cameraRight;
        }
        if (keyboard.IsKeyDown(KB::A)) {
            inputDir -= cameraRight;
        }
        if (keyboard.IsKeyDown(KB::W)) {
            inputDir += cameraForward;
        }
        if (keyboard.IsKeyDown(KB::S)) {
            inputDir -= cameraForward;
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

        if(keyboard.IsKeyTriggered(KB::Space)) {
            rb->AddForce(math::vector3f(0.0f, jumpForce, 0.0f));
		}
	}
}
