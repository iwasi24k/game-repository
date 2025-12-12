//==============================================================================
// File        : EnemyRespawn.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-11
// Last Update : 2025-12-11
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef ENEMY_RESPAWN_H
#define ENEMY_RESPAWN_H

#include "GameBehaviour.h"

class EnemyRespawn : public Framework::GameBehaviour {
private:
	bool m_IsSpawn = false;
	float m_SpawnTimer = 0.0f;

public:
	void Start() override;
	void Update() override;

	void Spawn(float time) { 
		m_IsSpawn = true;
		m_SpawnTimer = time; 
	}
};

#endif // ENEMY_RESPAWN_H