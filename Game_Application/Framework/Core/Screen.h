//==============================================================================
// File        : Screen.h
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
#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>

#define IS_WINDOW_MODE (FALSE)

namespace Framework {

	class Screen {
		UINT m_Width = 1280;
		UINT m_Height = 720;
		UINT m_FullWidth = 1280;
		UINT m_FullHeight = 720;

		Screen() {
			m_FullWidth = GetSystemMetrics(SM_CXSCREEN);
			m_FullHeight = GetSystemMetrics(SM_CYSCREEN);
		}
		~Screen() = default;
		Screen(const Screen&) = delete;
		Screen& operator=(const Screen&) = delete;

	public:
		static Screen& GetInstance() {
			static Screen instance;
			return instance;
		}
		float GetScreenWidth()  const { return static_cast<float>(IS_WINDOW_MODE ? m_Width : m_FullWidth); }
		float GetScreenHeight() const { return static_cast<float>(IS_WINDOW_MODE ? m_Height : m_FullHeight); }
	};
}

#define SCREEN_WIDTH (Framework::Screen::GetInstance().GetScreenWidth())
#define SCREEN_HEIGHT (Framework::Screen::GetInstance().GetScreenHeight())

#endif // SCREEN_H