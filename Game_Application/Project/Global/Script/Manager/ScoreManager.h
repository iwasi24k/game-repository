//==============================================================================
// File        : ScoreManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"
#include "Global/Prefab/ScorePrefab.h"

class ScoreManager : public Framework::ObjectManager {
private:
    static constexpr int kTotalScoreDigits = 5;
    std::vector<Framework::GameObject*> m_Scores;
    int m_OldScore = -1;

public:
    void Create() override;
    void Update() override;
};

#endif // SCORE_MANAGER_H