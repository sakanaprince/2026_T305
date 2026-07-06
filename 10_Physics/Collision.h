#pragma once
#include "../07_Math/Vector3.h"

namespace Collision
{
	/// <summary>
	/// 中心座標、半径
	/// </summary>
	struct Sphere
	{
		Vec3 centerPos;
		float radius;
	};

	/// <summary>
	/// 中心座標、中心座標からの各方向のサイズ
	/// </summary>
	struct Box
	{
		Vec3 centerPos;
		Vec3 scale;
	};

	bool IsHitSphereSphere(const Vec3& centerA, float radiusA, const Vec3& centerB, float radiusB);

	bool IsHitSphereSphere(const Sphere& sphereA, const Sphere& sphereB);

	bool IsHitSphereBox(const Vec3& s_Center, float radius, const Vec3& b_Center, const Vec3& scale);

	bool IsHitSphereBox(const Sphere& sphere, const Box& box);

	bool IsHitBoxBox(const Vec3& centerA, const Vec3& scaleA, const Vec3& centerB, const Vec3& scaleB);

	bool IsHitBoxBox(const Box& boxA, const Box& boxB);
}