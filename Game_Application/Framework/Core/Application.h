//==============================================================================
// File        : Application.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-06
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <cstddef>
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