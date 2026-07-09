#pragma once
#include "../07_Math/Vector3.h"
#include "../10_Physics/Collision.h"

class Trap
{
public:
	Trap(int _modelHandle, Vec3 _position) { Reset(_modelHandle, _position); }

	~Trap() = default;

	void Reset(int _modelHandle, Vec3 _position);
	void Draw() const;

	Collision::Box GetBox() const noexcept 
	{
		Collision::Box box;
		box.centerPos = position;
		box.scale = hitScale;
		return box;
	}

	float GetRadius() { return radius; }

	Vec3 GetHitScale() const { return hitScale; }

	int GetDamage() const { return damage; }

private:
	int modelHandle{ -1 };

	Vec3 position{ 0.0f,0.0f,0.0f };
	Vec3 scale{ 0.0f,0.0f,0.0f };
	Vec3 hitScale{ 30.0f, 10.0f, 30.0f };
	float radius{ 0.0f };
	int damage{ 3 };
};

