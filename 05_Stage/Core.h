#pragma once
class Core
{
public:
	Core() = default;
	~Core() = default;

	void Reset() { hp = hp_Max; }

	int GetHP() const { return hp; }
	void SetHP(int _hp) { hp = _hp; }

	void TakeDamage(int damage) { hp -= damage; }

private:
	int hp{ 0 };
	int hp_Max{ 1000 };
};

