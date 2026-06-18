#pragma once
#include "../01_Core/Entity.h"
#include "../02_Player/PlayerController.h"

class PlayerController;

class Enemy : public Entity
{
public:
	
	//敵クラスはプレイヤーの参照を持っている必要がある。当たり判定のために
	

	// Entity を介して継承されました
	//void Init(){} override;
	virtual void Update() {};  
	//基底クラスA....を継いだB...をさらに継いだCに,AのupdateをオーバーライドさせるにはBが
	//Updateをバーチャルで持っている必要がある

private:
	virtual void BodyLine() const {};

};

