//==============================================================================
// File        : Window.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-06
//------------------------------------------------------------------------------
// Overview :
// このクラスは、Windows アプリケーション用のメインウィンドウを作成・管理します。
// Initialize() でウィンドウクラス登録とウィンドウ生成を行い、
// ShowWindow と UpdateWindow で表示を行います。
// Shutdown() で破棄・クリーンアップを実施。
// ProcessMessage() により、PeekMessage を用いたメッセージループを処理。
// WndProc は静的関数として Windows メッセージを受け取り、
// ESC キーで終了やシステムメニュー無効化など基本操作を提供します。
//==============================================================================
#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

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