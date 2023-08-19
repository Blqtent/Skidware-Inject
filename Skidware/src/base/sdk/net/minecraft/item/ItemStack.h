#pragma once
#include "../../../Object.h"
#include "ItemArmor.h"
class CItemStack : public Object
{
	//CItemStack();

	//CItemStack(jobject instance);
	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	jobject GetItem();
	int GetItemID();
};