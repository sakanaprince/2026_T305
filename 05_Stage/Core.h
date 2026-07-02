#pragma once
#include <string>

class Core
{
public:
	Core() = default;
	~Core() = default;

	void Init();
	void Reset();
	void Update();
	void Draw() const;

	int GetHP() const { return hp; }
	void SetHP(int _hp) { hp = _hp; }

	void TakeDamage(int damage) { hp -= damage; }

private:
	int fontHandle{ -1 };

	int hp{ 0 };
	int hp_Max{ 100 };
	int hp_prev{ 0 };

	std::wstring text;
};

