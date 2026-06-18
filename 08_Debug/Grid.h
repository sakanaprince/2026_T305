#pragma once

class Grid
{
private:
	int halfCount{ 5 };
	float spacing{ 100.0f };

public:
	void Draw() const;
};

