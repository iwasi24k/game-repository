//==============================================================================
// File        : Timer.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Timer.h"

using namespace Framework;

void Timer::Initialize() {
	INT64 frequency = 0;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	m_SecondsPerCount = 1.0 / static_cast<double>(frequency);
	Reset();
}

void Timer::Reset() {
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_StartTime));
	m_PreviousTime = m_StartTime;
}

void Timer::Update() {
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_CurrentTime));
	m_DeltaTime = static_cast<float>((m_CurrentTime - m_PreviousTime) * m_SecondsPerCount);
	m_PreviousTime = m_CurrentTime;
}

float Timer::GetDeltaTime() {
	return m_DeltaTime;
}

float Timer::GetTotalTime() {
	return static_cast<float>((m_CurrentTime - m_StartTime) * m_SecondsPerCount);
}
