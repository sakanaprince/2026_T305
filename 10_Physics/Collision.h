#pragma once
#include "../07_Math/Vector3.h"

namespace Collision
{
	/// <summary>
	/// ’†SÀ•WA”¼Œa
	/// </summary>
	struct Sphere
	{
		Vec3 centerPos;
		float radius;
	};

	bool IsHitSphereSphere(const Vec3& centerA, float radiusA, const Vec3& centerB, float radiusB);

	bool IsHitSphereSphere(const Sphere& sphereA, const Sphere& sphereB);
}