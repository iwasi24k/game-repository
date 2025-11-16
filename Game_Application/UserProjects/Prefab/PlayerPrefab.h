#pragma once

#include "Framework/Scene/Prefab.h"
#include "Framework/Scene/GameObjectManager.h"
#include "../Scripts/PlayerScript.h"

class PlayerPrefab : public Framework::Prefab {
public:
    Framework::GameObject* Create(Framework::GameObjectManager* mgr) override {
        auto obj = mgr->CreateObject("Player");
		obj->AddComponent<PlayerScript>();
        Inspector(obj);
        return obj;
    }
    void Inspector(Framework::GameObject* obj) override {
    }
};