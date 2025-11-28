//==============================================================================
// File        : TopDownCamera.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-18
// Last Update : 2025-11-18
//------------------------------------------------------------------------------
//
//==============================================================================
#ifndef TOP_DOWN_CAMERA_H
#define TOP_DOWN_CAMERA_H

#include "Camera.h"
#include <string>
#include "MathTransform.h"

namespace Framework {

	struct TopDownCameraConfig {
		std::string targetTag = "None"; // 注視点の位置
		float height = 10.0f; // カメラの高さ
		float distance = 10.0f; // カメラとターゲットの距離
		float smooth = 10.0f; // カメラの追従速度
		float pitch = 0.0f;
		float yaw = 0.0f;
		float roll = 0.0f;
	};

	class TopDownCamera : public Camera {
	private:
		GameObject* m_TargetObject = nullptr; // 注視点のオブジェクト
		std::string m_TargetTag = "None"; // 注視点の位置
		float m_Height = 10.0f; // カメラの高さ
		float m_Distance = 10.0f; // カメラとターゲットの距離
		float m_Smooth = 10.0f; // カメラの追従速度
		math::vector3f m_Focus{};

	public:
		void Start() override;
		void Update() override;

		// Getter / Setter
		void SetTargetTag(const std::string& tag) { m_TargetTag = tag; }
		const std::string& GetTargetTag() const { return m_TargetTag; }
		void SetHeight(float height) { m_Height = height; }
		float GetHeight() const { return m_Height; }
		void SetDistance(float distance) { m_Distance = distance; }
		float GetDistance() const { return m_Distance; }
		void SetSmooth(float smooth) { m_Smooth = smooth; }
		float GetSmooth() const { return m_Smooth; }

	public:
		void Configure(const TopDownCameraConfig& config) {
			m_TargetTag = config.targetTag;
			m_Height = config.height;
			m_Distance = config.distance;
			m_Smooth = config.smooth;
			m_Rotation = { config.pitch, config.yaw, config.roll };
		}
	};
} // namespace Framework


#endif // TOP_DOWN_CAMERA_H
