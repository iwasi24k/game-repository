//==============================================================================
// File        : ResultScoreManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "ResultScoreManager.h"
#include "Global/Prefab/ScorePrefab.h"
#include "Global/GlobalGameData.h"
#include "Components/RenderComponent/SpriteComponent.h"

using namespace Framework;

void ResultScoreManager::Create() {
	ScorePrefab scorePrefab;
	for (int i = 0; i < kTotalScoreDigits; ++i) {
		auto scoreObj = scorePrefab.Create(GetGameObjectManager());
		scoreObj->GetTransform().position = { SCREEN_CENTER_W * 0.85f, SCREEN_CENTER_H * 1.03f, 1.0f };
		scoreObj->GetTransform().scale = { SCREEN_WIDTH * 0.14f, SCREEN_HEIGHT * 0.2f, 1.0f };

		scoreObj->GetTransform().position.x += i * (scoreObj->GetTransform().scale.x) * 0.5f;
		m_Scores.push_back(scoreObj);
	}

	int score = Global::GlobalGameData::GetInstance().GetScore();

	std::string scoreStr = std::to_string(score);

	int scoreLength = static_cast<int>(scoreStr.length());
	for (int i = 0; i < kTotalScoreDigits; ++i) {
		auto spriteComp = m_Scores[kTotalScoreDigits - 1 - i]->GetComponent<SpriteComponent>();
		if (spriteComp) {
			if (i < scoreLength) {
				char digitChar = scoreStr[scoreLength - 1 - i];
				int digit = digitChar - '0';
				float uStart = digit * 0.1f;
				spriteComp->SetUV(uStart, 0.0f, uStart + 0.1f, 1.0f);
			}
			else {
				spriteComp->SetUV(0.0f, 0.0f, 0.1f, 1.0f);
			}
		}
	}
}

void ResultScoreManager::Update() {

}