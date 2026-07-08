#pragma once
#include "../04_Resource/ResourceKeys.h"
#include "../07_Math/Vector3.h"
#include <string>
#include "../02_Player/PlayerController.h"

class SoundManager
{
public:
	SoundManager() = default;
	~SoundManager() = default;

	void Init(PlayerController* _player);

	//普通の音の再生
	void PlaySENormal(const int soundHandle);

	//距離減衰と音の左右差がある音の再生
	void PlaySEAtPosition(const int soundHandle, const Vec3& position);

private:
	PlayerController* player{ nullptr };

	//音の聞こえる最大距離
	float maxDistance{ 1500.0f };

	//音の音量とパン（音の左右の比率）の最大値
	int maxSoundAndPan{ 255 };
};

