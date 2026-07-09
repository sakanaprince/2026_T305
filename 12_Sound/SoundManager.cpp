#include "SoundManager.h"
#include "DxLib.h"
#include "../08_Debug/DebugUI.h"

void SoundManager::Init(PlayerController* _player)
{
	player = _player;
}

void SoundManager::PlaySENormal(const int soundHandle, int soundVolume)
{
	ChangeVolumeSoundMem(soundVolume, soundHandle);

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySEAtPosition(const int soundHandle, const Vec3& position)
{
	//プレイヤーから見た音の方向を取る
	Vec3 toPlayer = position - player->GetPosition();

	//プレイヤーとの距離を求める
	float length = toPlayer.Length();

	//最大距離より遠ければ音は鳴らさない
	if (length >= maxDistance) { return; }

	//現在距離と最大距離を使って０～１の範囲の値を取る
	float clampLength = length / maxDistance;

	//maxSoundをmaxSoound * clampLengthを書けて出た値で引くことで音量を調整
	int volume = static_cast<int>((float)maxSoundAndPan - (float)maxSoundAndPan * clampLength);

	//プレイヤーの前方と左右の方向を取る
	Vec3 forward = player->GetCameraForward();
	Vec3 right = { forward.z, 0.0f, -forward.x };
	Vec3 left = -right;

	//プレイヤーから見た敵の方向を正規化する
	Vec3 normalized = toPlayer.Normalized();

	//左右のドットを取る
	float rightDot = Vec3::Dot(right, normalized);
	float leftDot  = Vec3::Dot(left , normalized);

	int soundDot = 0;

	//数値の大きいほうだけ使う
	if (rightDot > 0)
	{
		//ドットが大きいほど値が大きくなるようにする
		soundDot = static_cast<int>((float)maxSoundAndPan * rightDot);
	}
	else if (leftDot > 0)
	{
		soundDot = static_cast<int>((float)maxSoundAndPan * leftDot);

		//左の音量はマイナスが大きいほど大きくなるのでマイナスにしておく
		soundDot *= -1;
	}

	//音の左右を調整
	ChangePanSoundMem(soundDot, soundHandle);

	//音量の設定
	ChangeVolumeSoundMem(volume, soundHandle);

	//音の再生
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
}
