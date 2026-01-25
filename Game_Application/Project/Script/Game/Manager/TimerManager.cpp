//==============================================================================
// File        : TimerManager.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2026-1-25
// Last Update : 2026-1-25
//------------------------------------------------------------------------------
//
//==============================================================================
#include "pch.h"
#include "TimerManager.h"
#include "Global/GlobalGameData.h"
#include "Components/RenderComponent/SpriteComponent.h"
#include "Framework/Core/Timer.h"
#include "Prefab/Game/TimerPrefab.h"

using namespace Framework;

void TimerManager::Create() {
	TimerPrefab timerPrefab;
	for (int i = 0; i < kTotalTimerDigits; ++i) {
		auto timerObj = timerPrefab.Create(GetGameObjectManager());
		timerObj->GetTransform().position = { SCREEN_CENTER_W * 0.96f, SCREEN_CENTER_H * 0.26f, 1.0f };
		timerObj->GetTransform().scale = { SCREEN_WIDTH * 0.11f, SCREEN_HEIGHT * 0.18f, 1.0f };
		timerObj->GetTransform().position.x += i * (timerObj->GetTransform().scale.x) * 0.31f;
		m_Timers.push_back(timerObj);
	}
}

void TimerManager::Update() {
	float dt = Timer::GetInstance().GetDeltaTime();

	m_ElapsedTime += dt;
	int elapsedSec = static_cast<int>(m_ElapsedTime);
	if (elapsedSec == m_LastElapsedSec) return;
	m_LastElapsedSec = elapsedSec;
	int timerCount = std::max(0, kInitialTime - elapsedSec);

	std::string timeStr = std::to_string(timerCount);

	int timeLength = static_cast<int>(timeStr.length());
	for (int i = 0; i < kTotalTimerDigits; ++i) {
		auto spriteComp = m_Timers[kTotalTimerDigits - 1 - i]->GetComponent<SpriteComponent>();
		if (spriteComp) {
			if (i < timeLength) {
				char digitChar = timeStr[timeLength - 1 - i];
				int digit = digitChar - '0';
				float uStart = digit * 0.1f;
				spriteComp->SetUV(uStart, 0.0f, uStart + 0.1f, 1.0f);
			}
			else {
				spriteComp->SetUV(0.0f, 0.0f, 0.1f, 1.0f);
			}
		}
	}

	if (timerCount > 3) return;

	for (auto& timer : m_Timers) {
		auto sprite = timer->GetComponent<SpriteComponent>();
		if (!sprite) continue;

		sprite->SetColor({ 0.85f, 0.0f, 0.0f, 1.0f }); // ê‘
	}

	if(timerCount <= 0) {
		Global::GlobalGameData::GetInstance().SetGameFinished(true);
	}
}