//==============================================================================
// File        : TitleCamera.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-12-04
// Last Update : 2025-12-04
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef TITLE_CAMERA_H
#define TITLE_CAMERA_H

#include "Framework/Scene/Components/CameraComponent/Camera.h"
#include <string>
#include "MathTransform.h"

struct TitleCameraConfig {
	float distance = 100.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;
};

class TitleCamera : public Framework::Camera {
private:
	math::vector3f m_Focus = { 0, 0, 0 };   // 初期値をタイトル中央に
	float m_Distance = 100.0f;

public:
	void Start() override;
	void Update() override;

public:
	void Configure(const TitleCameraConfig& config) {
		m_Distance = config.distance;
		m_Rotation = { config.pitch, config.yaw, config.roll };
	}
};	

#endif // TITLE_CAMERA_H
