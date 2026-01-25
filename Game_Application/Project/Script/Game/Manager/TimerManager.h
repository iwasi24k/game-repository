//==============================================================================
// File        : TimerManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"
#include "Global/Prefab/ScorePrefab.h"

class TimerManager : public Framework::ObjectManager {
private:
    static constexpr int kTotalTimerDigits = 2;
	static constexpr int kInitialTime = 60;
    float m_ElapsedTime = 0.0f;
    int m_LastElapsedSec = -1;

    std::vector<Framework::GameObject*> m_Timers;

public:
    void Create() override;
    void Update() override;
};

#endif // TIMER_MANAGER_H