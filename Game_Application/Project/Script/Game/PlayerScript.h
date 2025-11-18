#pragma once

#include "MonoBehaviour.h"
#include "Components/RenderComponent/SpriteComponent.h"

class PlayerScript : public Framework::MonoBehaviour {
public:
    void Start() override;
    void Update() override;
};
