#include "pch.h"
#include "Component.h"

#include "SceneManager.h"
#include "GameObjectManager.h"

using namespace Framework;

GameObject* Component::FindObject(const std::string& tag) {
    return SceneManager::GetInstance().GetCurrentScene()->GetGameObjectManager()->FindObject(tag);
}
