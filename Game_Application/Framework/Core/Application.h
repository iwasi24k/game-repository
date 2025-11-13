//==============================================================================
// File        : Application.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-06
//------------------------------------------------------------------------------
// Overview :
// Application クラスはゲームアプリケーション全体のライフサイクルを管理します。
// Initialize() で COM 初期化、ログ、タイマー、ウィンドウ、レンダラー、シェーダー、ゲーム初期化を順に実行。
// Shutdown() で全リソースの解放と COM 終了を行います。
// Run() はメインループとして、ウィンドウメッセージ処理、タイマー更新、ゲーム更新、描画を毎フレーム実行。
// これにより、統合された環境でスムーズにゲームやアプリケーションを動作させることが可能です。
//==============================================================================
#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "Window.h"

namespace Framework {

	class Application {
	private:
		HWND m_hWnd = nullptr;

		std::unique_ptr<Window> m_Window;

	public: // Application Loop
		Application();
		~Application();

		bool Initialize(HINSTANCE hInstance, int nCmdShow);
		void Shutdown();

		void Run();

	private: // Game Loop
		bool Init();
		void Update();
		void Draw();
		void Finalize();
	};
}

#endif // APPLICATION_H