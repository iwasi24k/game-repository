//==============================================================================
// File        : InputKeyboard.inl
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef INPUT_KEYBOARD_INL
#define INPUT_KEYBOARD_INL

enum class Key : int {
    // --- 基本 ---
    Escape = VK_ESCAPE,
    Space = VK_SPACE,
    Enter = VK_RETURN,
    Left = VK_LEFT,
    Right = VK_RIGHT,
    Up = VK_UP,
    Down = VK_DOWN,

    // --- アルファベット ---
    A = 'A', B = 'B', C = 'C', D = 'D', E = 'E',
    F = 'F', G = 'G', H = 'H', I = 'I', J = 'J',
    K = 'K', L = 'L', M = 'M', N = 'N', O = 'O',
    P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T',
    U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y', Z = 'Z',

    // --- 数字（テンキーではない）---
    Num0 = '0', Num1 = '1', Num2 = '2', Num3 = '3', Num4 = '4',
    Num5 = '5', Num6 = '6', Num7 = '7', Num8 = '8', Num9 = '9',

    // --- 修飾（左右区別あり）---
    LShift = VK_LSHIFT,
    RShift = VK_RSHIFT,
    LControl = VK_LCONTROL,
    RControl = VK_RCONTROL,
    LAlt = VK_LMENU,
    RAlt = VK_RMENU,

    // --- 共通修飾 ---
    Shift = VK_SHIFT,
    Control = VK_CONTROL,
    Alt = VK_MENU,

    Tab = VK_TAB,
    Backspace = VK_BACK,
    Delete = VK_DELETE
};

#endif // INPUT_KEYBOARD_INL