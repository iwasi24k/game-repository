//==============================================================================
// File        : Timer.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// Timer クラスは高精度のパフォーマンスカウンターを用いて時間を管理します。
// Initialize() で周波数を取得し、時間単位を計算。
// Reset() で計測開始時刻をリセット。
// Update() で前フレームとの経過時間を計算（DeltaTime）。
// GetDeltaTime() で直近フレームの経過時間、
// GetTotalTime() でアプリケーション開始からの総経過時間を取得可能。
// ゲームループやアニメーションのフレーム制御に不可欠です。
//==============================================================================
#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

namespace Framework {

	class Timer {
	private:
		INT64 m_StartTime = 0;
		INT64 m_PreviousTime = 0;
		INT64 m_CurrentTime = 0;

		double m_SecondsPerCount = 0.0;
		float m_DeltaTime = 0.0f;

		Timer() = default;
		~Timer() = default;
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

	public:
		static Timer& GetInstance() {
			static Timer instance;
			return instance;
		}

		void Initialize();

		void Reset();
		void Update();

		float GetDeltaTime();
		float GetTotalTime();
	};
}

#endif // TIMER_H