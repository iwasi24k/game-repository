//==============================================================================
// File        : GameScene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-16
// Last Update : 2025-11-16
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Scene.h"

class GameScene : public Framework::Scene {
public:
	bool SceneInitialize() override;
	void SceneFinalize() override;
	void SceneUpdate() override;
};

#endif // GAME_SCENE_H
