#include "BuyAmulet.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyAmulet::PurchaseItem()
{
	pShopManager->GetGameContext()->GetPlayer().ResurrectionAmuletPlus();
}
