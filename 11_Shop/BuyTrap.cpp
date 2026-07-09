#include "BuyTrap.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyTrap::PurchaseItem()
{
	pShopManager->GetGameContext()->BuyTrap();
}
