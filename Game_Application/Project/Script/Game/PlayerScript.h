#pragma once

#include "MonoBehaviour.h"
#include "Components/RenderComponent/SpriteComponent.h"

class PlayerScript : public Framework::MonoBehaviour {
public:
	Framework::GameObject* testObject;
    void Start() override {
        // Initialization code here
        testObject = FindObject("Test");
		testObject->GetComponent<Framework::SpriteComponent>()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    }

    void Update() override {
        // Update code here
		GetOwner()->GetTransform().position.x += 0.01f;
		GetOwner()->GetTransform().rotation.y += 0.01f;
        testObject->GetTransform().position.y += 1.0f;
    }
};
