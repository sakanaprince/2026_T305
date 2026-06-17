#pragma once
#include "DxPlus.h"
#include "../07_Math/Vector3.h"

class CameraController
{
public:
	void Reset();
	void Update(float deltaTime);

private:
	Vec3 eye{ 600.0f,600.0f,-600.0f };
	Vec3 target{ 0.0f,0.0f,0.0f };
	Vec3 up{ 0.0f,1.0f,0.0f };

	DxPlus::Vec2Int currentMouse{ 0,0 };
	DxPlus::Vec2Int prevMouse{ 0,0 };

	float yaw{ 0.0f };
	float pitch{ 0.0f };
	float distance{ 400.0f };
	float dx{ 0.0f };
	float dy{ 0.0f };

	bool hasPrevMouse{ false };

	static constexpr float ROTATE_RAD_PAR_PIXEL{ DxPlus::PI * 2 / DxPlus::CLIENT_WIDTH };
	static constexpr float PITC_MIN{ DxPlus::Deg2Rad * -89 };
	static constexpr float PITC_MAX{ DxPlus::Deg2Rad * 89 };
	static constexpr float ZOOM_SPEED_PER_WHEEL{ 4000.0f };
	static constexpr float DISTANCE_MIN{ 50.0f };
	static constexpr float DISTANCE_MAX{ 2000.0f };
	static constexpr float MOVE_SPEED{ 400.0f };
};

