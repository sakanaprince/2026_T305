#include "Collision.h"

bool Collision::IsHitSphereSphere(const Vec3& centerA, float radiusA, const Vec3& centerB, float radiusB)
{
	Vec3 diff = centerA - centerB;
	float radiusSum = radiusA + radiusB;

	return (diff.LengthSq() <= radiusSum * radiusSum);
}

bool Collision::IsHitSphereSphere(const Sphere& sphereA, const Sphere& sphereB)
{
	return IsHitSphereSphere(sphereA.centerPos, sphereA.radius, sphereB.centerPos, sphereB.radius);
}
