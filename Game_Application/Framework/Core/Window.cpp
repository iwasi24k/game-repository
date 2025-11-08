//==============================================================================
// File        : Window.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "Window.h"
#include "DebugTool.h"

using namespace Framework;

const wchar_t* CLASS_NAME = L"AppClass";
const wchar_t* WINDOW_NAME = L"DX11-3DÉQÅ[ÉÄ";

Window::Window() {}
Window::~Window() { Shutdown(); }

bool Window::Initialize(HINSTANCE hInstance, int nCmdShow) {
    m_hInstance = hInstance;

    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    if (!RegisterClassEx(&wc)) { return false; }

    RECT rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        WINDOW_NAME,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!m_hWnd) { return false; }

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    LOG_IF(L"Window Initialize Completed");
    return true;
}

void Window::Shutdown() {
    LOG_IF(L"Window Shutdown..");

    if (m_hWnd) {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }

    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessage() {
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) { return false; }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

// ê√ìIWndProc
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            DestroyWindow(hWnd);
        }

        return 0;

    case WM_SYSCOMMAND:
        if ((wParam & 0xFFF0) == SC_KEYMENU)
            return 0;
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
