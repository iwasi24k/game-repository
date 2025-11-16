#include "pch.h"
#include "GameScene.h"
#include "../Prefab/PlayerPrefab.h"

bool GameScene::SceneInitialize() {
	PlayerPrefab playerPrefab;
	playerPrefab.Create(GetGameObjectManager());
    return true;
}
