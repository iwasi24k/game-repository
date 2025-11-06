//==============================================================================
// File        : Window.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-06
//------------------------------------------------------------------------------
// Overview :
// 
//==============================================================================
#ifndef WINDOW_H
#define WINDOW_H

#include "pch.h"

namespace Framework {

	class Window {
	private:
		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		Window();
		~Window();

		bool Initialize(HINSTANCE hInstance, int nCmdShow);
		void Shutdown();

		bool ProcessMessage();

		HWND GetHWnd() const { return m_hWnd; }
	};
}

#endif // WINDOW_H