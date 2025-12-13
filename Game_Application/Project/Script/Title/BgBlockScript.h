//==============================================================================
// File        : BgBlockScript.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-05
// Last Update : 2025-12-05
//------------------------------------------------------------------------------
// 
//==============================================================================
#ifndef BG_BLOCK_SCRIPT_H
#define BG_BLOCK_SCRIPT_H

#include "GameBehaviour.h"
#include "Material.h"

class BgBlockScript : public Framework::GameBehaviour {
private:
    math::vector3f m_RotSpeed;
    float m_CurvePhase;
    float m_FallSpeed;
    float m_CurveAmplitude;
    float m_CurveFrequency;
    float m_MaxY, m_MinY;
    float m_MaxR, m_MinR;

    float m_MaxTime = 0.0f;
    float m_StartTimer = 0.0f;

    bool m_IsAvoiding = false;
    float m_HermiteStartX;
    float m_HermiteMid1X;
    float m_HermiteMid2X;
    float m_HermiteEndX;

public:
	void Start() override;
	void Update() override;

    void FallStartTime(float time) { m_MaxTime = time; }

private:
    float Hermite(float p0, float p1, float p2, float p3, float t);
};

#endif // BG_BLOCK_SCRIPT_H