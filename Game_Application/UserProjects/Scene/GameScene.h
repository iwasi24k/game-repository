#pragma once

#include "Framework/Scene/Scene.h"

class GameScene : public Framework::Scene {
public:
	bool SceneInitialize() override;
	void SceneFinalize() override;
	void SceneUpdate() override;
};
