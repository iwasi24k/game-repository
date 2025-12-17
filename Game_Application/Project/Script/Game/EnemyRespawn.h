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

public:
	void Start() override;
	void Update() override;

	void Spawn() { 
		m_IsSpawn = true;
	}
};

#endif // ENEMY_RESPAWN_H