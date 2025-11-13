//==============================================================================
// File        : InputMouse.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-08-20
// Last Update : 2025-08-29
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "InputMouse.h"
#include "DebugTool.h"

using namespace Framework;

void InputMouse::Initialize(HWND hwnd) {
    m_hWnd = hwnd;
    LOG_IF(L"InputMouse Initialize Completed");
}

void InputMouse::Update() {
    // マウスボタン（WndProcベース）
    for (int i = 0; i < 3; ++i) {
        m_MousePrevButton[i] = m_MouseButton[i];
        m_MouseButton[i] = m_MouseDownTemp[i];
    }

    // マウス座標
    POINT pos;
    if (GetCursorPos(&pos) && m_hWnd) {
        if (ScreenToClient(m_hWnd, &pos)) {
            m_MousePos = pos;

            math::vector2f currentPos{ static_cast<float>(pos.x), static_cast<float>(pos.y) };

            if (s_FirstUpdate) {
                s_LastMousePos = currentPos;
                s_FirstUpdate = false;
            }

            // 相対移動量は現在位置 - 前回位置
            s_MouseRelativeMovement = currentPos - s_LastMousePos;

            // 次回のために位置更新
            s_LastMousePos = currentPos;
        }
    }

    s_WheelDeltaCached = m_WheelDelta;
    m_WheelDelta = 0;  // 毎フレームクリア
}

bool InputMouse::IsMouseDown(MouseButton button) {
    int idx = static_cast<int>(button);
    return (idx >= 0 && idx < 3) ? m_MouseButton[idx] : false;
}

bool InputMouse::IsMouseClicked(MouseButton button) {
    int idx = static_cast<int>(button);
    return (idx >= 0 && idx < 3) ? (m_MouseButton[idx] && !m_MousePrevButton[idx]) : false;
}

bool InputMouse::IsMouseReleased(MouseButton button) {
    int idx = static_cast<int>(button);
    return (idx >= 0 && idx < 3) ? (!m_MouseButton[idx] && m_MousePrevButton[idx]) : false;
}

math::vector2f InputMouse::GetMousePosition() {
    POINT& pt = m_MousePos;

    return math::vector2f{ static_cast<float>(pt.x), static_cast<float>(pt.y) };
}

int InputMouse::GetWheelDelta() {
    return s_WheelDeltaCached / WHEEL_DELTA;
}

bool InputMouse::HitBox(const math::vector2f& center, const math::vector2f& size, float rotationRad) {
    math::vector2f mouse = GetMousePosition();

    // ワールド座標 → ローカル（オブジェクト中心基準）へ
    math::vector2f local = mouse - center;

    // 逆回転して軸揃えに変換
    float cosT = std::cos(-rotationRad);
    float sinT = std::sin(-rotationRad);

    math::vector2f rotated;
    rotated.x = local.x * cosT - local.y * sinT;
    rotated.y = local.x * sinT + local.y * cosT;

    float halfW = size.x * 0.5f;
    float halfH = size.y * 0.5f;

    return (
        rotated.x >= -halfW && rotated.x <= halfW &&
        rotated.y >= -halfH && rotated.y <= halfH
        );
}

void InputMouse::DisplayMouse(bool display) {
    if (display)
        while (::ShowCursor(TRUE) < 0);  // 表示数が0以上になるまで表示
    else
        while (::ShowCursor(FALSE) >= 0); // 表示数が負になるまで非表示
}

void InputMouse::EnableCursorLock(bool enable) {
    s_CursorLockEnabled = enable;
}

void InputMouse::LockCursorCenter() {
    if (!s_CursorLockEnabled) return;
    if (!m_hWnd) return;

    RECT rect{};
    if (::GetClientRect(m_hWnd, &rect)) {
        POINT center{};
        center.x = (rect.right - rect.left) / 2;
        center.y = (rect.bottom - rect.top) / 2;

        ::ClientToScreen(m_hWnd, &center);  // クライアント → スクリーン座標へ変換
        ::SetCursorPos(center.x, center.y); // スクリーン上の中央にカーソルを移動

        // 次回の相対移動計算のためにリセット
        math::vector2f clientCenter{ static_cast<float>(center.x), static_cast<float>(center.y) };
        ScreenToClient(m_hWnd, &center); // 再度クライアント座標に戻す
        clientCenter = math::vector2f{ static_cast<float>(center.x), static_cast<float>(center.y) };
        ResetLastMousePosition(clientCenter);
    }
}

math::vector2f InputMouse::GetMouseRelativeMovement() {
    return s_MouseRelativeMovement;
}

void InputMouse::ResetLastMousePosition(const math::vector2f& pos) {
    s_LastMousePos = pos;
}

//---プライベート関数--------------------------------------------------------------------------------------------------------

void InputMouse::OnMouseDown(int button) {
    if (button >= 0 && button < 3)
        m_MouseDownTemp[button] = true;
}

void InputMouse::OnMouseUp(int button) {
    if (button >= 0 && button < 3)
        m_MouseDownTemp[button] = false;
}

void InputMouse::OnWheel(short delta) {
    m_WheelDelta += delta;
}
