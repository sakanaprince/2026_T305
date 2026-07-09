#pragma once
#include "../04_Resource/ResourceKeys.h"
#include "../07_Math/Vector3.h"
#include <string>

class PlayerController;
class SoundManager
{
public:
	SoundManager() = default;
	~SoundManager() = default;

	void Init(PlayerController* _player);

	/// <summary>
	/// 通常の音の再生
	/// </summary>
	/// <param name="soundHandle">音のハンドル</param>
	/// <param name="soundVolume">音の大きさ。０～２５５で設定</param>
	void PlaySENormal(const int soundHandle , int soundVolume = 255);

	/// <summary>
	/// 距離減衰と音の左右差がある音の再生
	/// </summary>
	/// <param name="soundHandle">音のハンドル</param>
	/// <param name="position">音のなる位置</param>
	void PlaySEAtPosition(const int soundHandle, const Vec3& position);

private:
	PlayerController* player{ nullptr };

	//音の聞こえる最大距離
	float maxDistance{ 1500.0f };

	//音の音量とパン（音の左右の比率）の最大値
	int maxSoundAndPan{ 255 };
};

