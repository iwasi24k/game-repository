//==============================================================================
// File        : ResultScoreManager.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef RESULT_SCORE_MANAGER_H
#define RESULT_SCORE_MANAGER_H

#include <vector>
#include "GameObject.h"
#include "ObjectManager.h"
#include "Global/Prefab/ScorePrefab.h"

class ResultScoreManager : public Framework::ObjectManager {
private:
    static constexpr int kTotalScoreDigits = 5;
    std::vector<Framework::GameObject*> m_Scores;

public:
    void Create() override;
    void Update() override;
};

#endif // RESULT_SCORE_MANAGER_H