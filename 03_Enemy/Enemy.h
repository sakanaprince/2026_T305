#pragma once
#include "../01_Core/Entity.h"
#include "../02_Player/PlayerController.h"

class Enemy : public Entity
{
public:
	
	//敵クラスはプレイヤーの参照を持っている必要がある。当たり判定のために
	void SetPlayerPointer(PlayerController* pc) { playerCont = pc; };

	virtual void Update() {};  
	//基底クラスA....を継いだB...をさらに継いだCに,AのupdateをオーバーライドさせるにはBが
	//Updateをバーチャルで持っている必要がある

protected:
	virtual void BodyLine() const {};

	float animTimer{ 0.0f };

	PlayerController* playerCont;

};

