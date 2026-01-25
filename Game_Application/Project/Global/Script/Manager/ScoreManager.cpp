//==============================================================================
// File        : ScoreManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "ScoreManager.h"
#include "Global/Prefab/ScorePrefab.h"
#include "Global/GlobalGameData.h"
#include "Components/RenderComponent/SpriteComponent.h"

using namespace Framework;

void ScoreManager::Create() {
	ScorePrefab scorePrefab;
	for(int i = 0; i < kTotalScoreDigits; ++i) {
		auto scoreObj = scorePrefab.Create(GetGameObjectManager());
		scoreObj->GetTransform().position.x += i * (scoreObj->GetTransform().scale.x) * 0.5f;
		m_Scores.push_back(scoreObj);
	}
}

void ScoreManager::Update() {
	int score = Global::GlobalGameData::GetInstance().GetScore();
	if (score == m_OldScore) return;
	m_OldScore = score;

	std::string scoreStr = std::to_string(score);
	
	int scoreLength = static_cast<int>(scoreStr.length());
	for(int i = 0; i < kTotalScoreDigits; ++i) {
		auto spriteComp = m_Scores[kTotalScoreDigits - 1 - i]->GetComponent<SpriteComponent>();
		if(spriteComp) {
			if(i < scoreLength) {
				char digitChar = scoreStr[scoreLength - 1 - i];
				int digit = digitChar - '0';
				float uStart = digit * 0.1f;
				spriteComp->SetUV(uStart, 0.0f, uStart + 0.1f, 1.0f);
			} else {
				spriteComp->SetUV(0.0f, 0.0f, 0.1f, 1.0f);
			}
		}
	}
}