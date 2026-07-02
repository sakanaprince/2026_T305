#include "Core.h"
#include <DxLib.h>
#include "../DxPlus/DxPlus.h"
#include "../08_Debug/DebugUI.h"

#define DST_LEN (256)

void Core::Init()
{
	fontHandle = RM().GetFont(ResourceKeys::Font_ManufacturingConsent);
}

void Core::Reset()
{
	hp = hp_Max;
	hp_prev = hp;
	text = std::to_wstring(hp);
}

void Core::Update()
{
	if (hp != hp_prev)
	{
		text = std::to_wstring(hp);
		hp_prev = hp;
	}
}

void Core::Draw() const
{
	DrawLine(0, 75, DxPlus::CLIENT_WIDTH * 0.5 - 60, 75, GetColor(0, 0, 0), 2);
	DrawLine(DxPlus::CLIENT_WIDTH * 0.5 + 60, 75, DxPlus::CLIENT_WIDTH, 75, GetColor(0, 0, 0), 2);

	DrawCircle(DxPlus::CLIENT_WIDTH * 0.5, 75, 60, GetColor(0, 0, 0), false, 2);


	DxPlus::Text::DrawString(
		text.c_str(),
		{DxPlus::CLIENT_WIDTH * 0.5f, 50},
		GetColor(0, 0, 0),
		DxPlus::Text::TextAlign::TOP_CENTER,
		{1.3f,1.3f},
		0.0,
		fontHandle);
}
