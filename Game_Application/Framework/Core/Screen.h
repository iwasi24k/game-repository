//==============================================================================
// File        : Screen.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-08
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// Screen クラスは、アプリケーションの画面解像度を一元的に管理するシングルトンです。
// ウィンドウモードとフルスクリーンモード双方に対応し、現在利用すべき横幅・縦幅を返します。
// Windows API を用いてディスプレイの最大解像度を取得し、
// SCREEN_WIDTH / SCREEN_HEIGHT のマクロを通して描画系全体が参照できる基盤を提供します。
//==============================================================================
#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>

#if _DEBUG
#define IS_WINDOW_MODE (TRUE)
#else
#define IS_WINDOW_MODE (FALSE)
#endif

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

// screen position : left 0.0 / right SCREEN_WIDTH
#define SCREEN_WIDTH (Framework::Screen::GetInstance().GetScreenWidth())
// screen position : top 0.0 / bottom SCREEN_HEIGHT
#define SCREEN_HEIGHT (Framework::Screen::GetInstance().GetScreenHeight())
// screen position : left 0.0 / right SCREEN_WIDTH
#define SCREEN_CENTER_W (SCREEN_WIDTH / 2)
// screen position : top 0.0 / bottom SCREEN_HEIGHT
#define SCREEN_CENTER_H (SCREEN_HEIGHT / 2)

#endif // SCREEN_H