//==============================================================================
// File        : ResultScene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-1-22
// Last Update : 2025-1-22
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "Scene.h"
#include "Script/Game/Manager/BlockManager.h"

class ResultScene : public Framework::Scene {
public:
	bool SceneInitialize() override;
	void SceneFinalize() override;
	void SceneUpdate() override;

};

#endif // RESULT_SCENE_H