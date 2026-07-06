#include "BuyHolySushi.h"
#include "ShopManager.h"
#include "../01_Core/GameContext.h"

void BuyHolySushi::PurchaseItem()
{
	constexpr int damage{ 100 };
	constexpr float delay{ 5.0f };
	pShopManager->GetGameContext()->GetEnemySpawner().ReadyAllEnemyTakeDamage(damage, delay);
}
