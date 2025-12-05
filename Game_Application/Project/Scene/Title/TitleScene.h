//==============================================================================
// File        : TitleScene.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Scene.h"
#include "Script/Game/Manager/BlockManager.h"

class TitleScene : public Framework::Scene {
public:
	bool SceneInitialize() override;
	void SceneFinalize() override;
	void SceneUpdate() override;

};

#endif // TITLE_SCENE_H
