//==============================================================================
// File        : BgBlockScript.cpp
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#include "pch.h"
#include "BgBlockScript.h"
#include "Framework/Core/Timer.h"
#include "GameObject.h"
#include "Components/RenderComponent/ModelComponent.h"
#include "Material.h"

using namespace Framework;

//void BgBlockScript::Start() {
//    float rotSpeed = 1.5f;
//    m_RotSpeed = { Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed) };
//    m_CurvePhase = Random(0.0f, 2.0f * 3.14159f);
//    m_MaxY = 25.0f;
//    m_MinY = -15.0f;
//    m_FallSpeed = 2.0f;
//    m_CurveAmplitude = 1.0f;
//    m_CurveFrequency = 0.01f;
//    m_MinR = 30.0f;
//    m_MaxR = 35.0f;
//
//    float r = Random(m_MinR, m_MaxR);
//    float theta = Random(0.0f, 2.0f * 3.14159f);
//    auto& pos = GetOwner()->GetTransform().position;
//    pos = { r * cos(theta), m_MaxY, r * sin(theta) };
//
//    auto modelComp = GetOwner()->GetComponent<ModelComponent>();
//    if (modelComp) {
//        float c = Random(0.0f, 1.0f) < 0.5f ? 0.35f : 0.9f;
//        Material mat;
//        mat.Ambient = { 0.2f,0.2f,0.2f,1.0f };
//        mat.Diffuse = { c, c, c, 1.0f };
//        mat.Specular = { 0.2f,0.2f,0.2f,1.0f };
//        mat.Emission = { 0.2f,0.2f,0.2f,1.0f };
//        mat.Shininess = 32.0f;
//        modelComp->SetMaterial(mat);
//    }
//}
//
//void BgBlockScript::Update() {
//    auto dt = Timer::GetInstance().GetDeltaTime();
//    if (m_StartTimer < m_MaxTime) {
//        m_StartTimer += dt;
//        return;
//    }
//
//    float rotSpeed = 1.5f;
//
//    auto& pos = GetOwner()->GetTransform().position;
//
//    // 回転
//    GetOwner()->GetTransform().rotation += m_RotSpeed * dt;
//
//    // Y下降
//    pos.y -= m_FallSpeed * dt;
//
//    // X方向微カーブ
//    pos.x += m_CurveAmplitude * sin(m_CurveFrequency * pos.y + m_CurvePhase) * dt;
//
//    // 下限に達したら再生成（ドーナツ状）
//    if (pos.y < m_MinY) {
//        float r = Random(m_MinR, m_MaxR);
//        float theta = Random(0.0f, 2.0f * 3.14159f);
//        pos = { r * cos(theta), m_MaxY, r * sin(theta) };
//        m_RotSpeed = { Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed) };
//        m_CurvePhase = Random(0.0f, 2.0f * 3.14159f);
//    }
//}
// Hermite補間（4点版）
float BgBlockScript::Hermite(float p0, float p1, float p2, float p3, float t) {
    float t2 = t * t;
    float t3 = t2 * t;
    float h00 = 2 * t3 - 3 * t2 + 1;
    float h10 = t3 - 2 * t2 + t;
    float h01 = -2 * t3 + 3 * t2;
    float h11 = t3 - t2;

    float m0 = p1 - p0;
    float m1 = p3 - p2;
    return h00 * p0 + h10 * m0 + h01 * p3 + h11 * m1;
}

void BgBlockScript::Start() {
    m_MaxY = 26.0f;
    m_MinY = -10.0f;
    m_MinR = 30.0f;
    m_MaxR = 45.0f;
    float rotSpeed = 1.0f;

    float minFall = 1.5f;
    float maxFall = 2.0f;
    m_FallSpeed = Random(minFall, maxFall);

    // 初期位置をドーナツ状にランダム配置
    auto& pos = GetOwner()->GetTransform().position;
    float r = Random(m_MinR, m_MaxR);
    float theta = Random(0.0f, 2.0f * 3.14159f);
    pos.x = r * cos(theta);
    pos.y = m_MaxY;
    pos.z = r * sin(theta);

    // Hermite補間用のX座標を初期設定
    float hermite = 20.0f;
    m_HermiteStartX = pos.x;
    m_HermiteMid1X = pos.x + Random(-hermite, hermite);
    m_HermiteMid2X = pos.x + Random(-hermite, hermite);
    m_HermiteEndX = pos.x + Random(-hermite, hermite);

    auto& blockScale = GetOwner()->GetTransform().scale;
    float minScale = 0.5f;
    float maxScale = 1.5f;
    float randomScale = Random(minScale, maxScale);
    for (auto& scale : blockScale) scale = randomScale;

    // ランダム回転
    m_RotSpeed = { Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed) };

    // 色ランダム
    auto modelComp = GetOwner()->GetComponent<ModelComponent>();
    if (modelComp) {
        float c = Random(0.0f, 1.0f) < 0.5f ? 0.35f : 0.9f;
        Material mat;
        mat.Ambient = { 0.2f,0.2f,0.2f,1.0f };
        mat.Diffuse = { c, c, c, 1.0f };
        mat.Specular = { 0.2f,0.2f,0.2f,1.0f };
        mat.Emission = { 0.2f,0.2f,0.2f,1.0f };
        mat.Shininess = 32.0f;
        modelComp->SetMaterial(mat);
    }
}

void BgBlockScript::Update() {
    float dt = Timer::GetInstance().GetDeltaTime();
    if (m_StartTimer < m_MaxTime) {
        m_StartTimer += dt;
        return;
    }
    auto& pos = GetOwner()->GetTransform().position;

    // 回転
    GetOwner()->GetTransform().rotation += m_RotSpeed * dt;

    // Y下降
    pos.y -= m_FallSpeed * dt;

    // 滑らかなX補間
    float t = (m_MaxY - pos.y) / (m_MaxY - m_MinY);
    t = std::clamp(t, 0.0f, 1.0f);
    pos.x = Hermite(m_HermiteStartX, m_HermiteMid1X, m_HermiteMid2X, m_HermiteEndX, t);

    // 下限で再生成
    if (pos.y < m_MinY) {
        pos.y = m_MaxY;

        // Z座標はドーナツ状にランダム再生成
        float r = Random(m_MinR, m_MaxR);
        float theta = Random(0.0f, 2.0f * 3.14159f);
        pos.z = r * sin(theta);
        m_HermiteStartX = r * cos(theta);

        // 新しいHermite補間点設定
        m_HermiteMid1X = m_HermiteStartX + Random(-2.0f, 2.0f);
        m_HermiteMid2X = m_HermiteStartX + Random(-2.0f, 2.0f);
        m_HermiteEndX = m_HermiteStartX + Random(-2.0f, 2.0f);

        // 新しい回転
        float rotSpeed = 1.5f;
        m_RotSpeed = { Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed), Random(-rotSpeed, rotSpeed) };
    }
}
