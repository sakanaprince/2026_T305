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

bool Collision::IsHitSphereBox(const Vec3& s_Center, float radius, const Vec3& b_Center, const Vec3& scale)
{
	float left   = b_Center.x - scale.x;
	float right  = b_Center.x + scale.x;
	float top    = b_Center.y + scale.y;
	float bottom = b_Center.y - scale.y;
	float front  = b_Center.z + scale.z;
	float back   = b_Center.z - scale.z;

	float x = (s_Center.x < left)   ? left   : (s_Center.x > right) ? right : s_Center.x;
	float y = (s_Center.y < bottom) ? bottom : (s_Center.y > top)   ? top   : s_Center.y;
	float z = (s_Center.z < back)   ? back   : (s_Center.z > front) ? front : s_Center.z;

	float dx = s_Center.x - x;
	float dy = s_Center.y - y;
	float dz = s_Center.z - z;
	float d = (dx * dx) + (dy * dy) + (dz * dz);
	float r = radius * radius;

	return d < r;
}

bool Collision::IsHitSphereBox(const Sphere& sphere, const Box& box)
{
	return IsHitSphereBox(sphere.centerPos, sphere.radius, box.centerPos, box.scale);
}

bool Collision::IsHitBoxBox(const Vec3& centerA, const Vec3& scaleA, const Vec3& centerB, const Vec3& scaleB)
{
	float leftA   = centerA.x - scaleA.x;
	float rightA  = centerA.x + scaleA.x;
	float topA    = centerA.y + scaleA.y;
	float bottomA = centerA.y - scaleA.y;
	float frontA  = centerA.z + scaleA.z;
	float backA   = centerA.z - scaleA.z;

	float leftB   = centerB.x - scaleB.x;
	float rightB  = centerB.x + scaleB.x;
	float topB    = centerB.y + scaleB.y;
	float bottomB = centerB.y - scaleB.y;
	float frontB  = centerB.z + scaleB.z;
	float backB   = centerB.z - scaleB.z;

	if (leftA <= rightB && rightA >= leftB &&
		bottomA <= topB && topA >= bottomB &&
		backA <= frontB && frontA >= backB)
	{
		return true;
	}

	return false;
}

bool Collision::IsHitBoxBox(const Box& boxA, const Box& boxB)
{
	return IsHitBoxBox(boxA.centerPos, boxA.scale, boxB.centerPos, boxB.scale);
}
