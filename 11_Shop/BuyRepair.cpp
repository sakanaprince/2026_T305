#include "BuyRepair.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyRepair::PurchaseItem()
{	
	auto gC = pShopManager->GetGameContext();
	gC->GetCore().SetHP(gC->GetCore().GetHP() + 30);
}
