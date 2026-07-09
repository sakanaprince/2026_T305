#include "BuyHeal.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyHeal::PurchaseItem()
{
	pShopManager->GetGameContext()->GetPlayer().HealHp();
}
