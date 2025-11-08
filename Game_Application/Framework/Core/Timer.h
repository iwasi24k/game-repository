//==============================================================================
// File        : Timer.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// タイマー管理
//==============================================================================
#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

namespace Framework {

	class Timer {
	private:
		static inline INT64 m_StartTime = 0;
		static inline INT64 m_PreviousTime = 0;
		static inline INT64 m_CurrentTime = 0;

		static inline double m_SecondsPerCount = 0.0;
		static inline float m_DeltaTime = 0.0f;

	public:
		static void Initialize();

		static void Reset();
		static void Update();

		static float GetDeltaTime();
		static float GetTotalTime();
	};
}

#endif // TIMER_H