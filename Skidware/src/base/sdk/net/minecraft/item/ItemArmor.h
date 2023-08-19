#pragma once
#include "item.h"
#include "../../../Object.h"
#include "ItemStack.h"
class CItemArmor : public CItem
{
public:
	using CItem::CItem;
	int getColor(jobject stack);
};