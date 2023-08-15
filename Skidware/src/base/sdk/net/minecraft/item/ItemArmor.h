#pragma once
#include "item.h"
#include "../../../java/IClass.h"
#include "ItemStack.h"
struct CItemArmor : CItem
{
	CItemArmor();

	CItemArmor(jobject instance);
	jclass GetClass();
	jobject GetInstance();

	int getColor(jobject stack);


};