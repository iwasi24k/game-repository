//==============================================================================
// File        : InputKeyboard.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "InputKeyboard.h"
#include "DebugTool.h"

using namespace Framework;

void InputKeyboard::Initialize(HWND hwnd) {
    m_hWnd = hwnd;
    GetKeyboardState(m_PreviousKey);
    GetKeyboardState(m_CurrentKey);
    LOG_IF(L"InputKeyboard Initialize Completed");
}

void InputKeyboard::Update() {
    // キーボード
    memcpy(m_PreviousKey, m_CurrentKey, 256);
    GetKeyboardState(m_CurrentKey);
}

bool InputKeyboard::IsKeyDown(Key key) {
    int k = static_cast<int>(key);
    return (m_CurrentKey[k] & 0x80) != 0;
}

bool InputKeyboard::IsKeyTriggered(Key key) {
    int k = static_cast<int>(key);
    return (m_CurrentKey[k] & 0x80) != 0 && (m_PreviousKey[k] & 0x80) == 0;
}

bool InputKeyboard::IsKeyReleased(Key key) {
    int k = static_cast<int>(key);
    return (m_CurrentKey[k] & 0x80) == 0 && (m_PreviousKey[k] & 0x80) != 0;
}