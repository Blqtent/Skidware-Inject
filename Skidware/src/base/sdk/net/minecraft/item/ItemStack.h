#pragma once
#include "../../../java/IClass.h"
#include "ItemArmor.h"
struct CItemStack : IClass
{
	CItemStack();

	CItemStack(jobject instance);
	jclass GetClass();
	jobject GetInstance();

	jobject GetItem();
	int GetItemID();
};