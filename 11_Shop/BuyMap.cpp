#include "BuyMap.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyMap::PurchaseItem()
{
	//ゲームコンテキストにマップ解放処理を書いてもらう
	pShopManager->GetGameContext()->UnlockMap();
}
