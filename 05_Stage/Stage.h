#pragma once

class Stage
{
public:
	Stage() = default;
	~Stage() = default;

	void Init();
	void Reset();
	void Update();
	void Draw() const;

private:
};

