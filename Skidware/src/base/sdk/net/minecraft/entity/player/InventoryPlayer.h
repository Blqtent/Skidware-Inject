#pragma once

#include "../../../../Object.h"
#include "../../item/ItemStack.h"

class CInventoryPlayer :public Object
{

public:
	using Object::Object;
	CItemStack GetCurrentItem();
	void SetCurrentItem(int index);
	CItemStack GetIndexItem(int index);
	CItemStack GetArmorItem(int index);
};