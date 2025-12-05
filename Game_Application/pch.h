//==============================================================================
// File        : pch.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// 汎用 include&マクロ定義
//==============================================================================
#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <Windows.h>
#include <assert.h>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


#include <DirectXMath.h>
using namespace DirectX;

#include "DirectXTex.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

#define IS_WINDOW_MODE (TRUE)

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


#endif // PCH_H