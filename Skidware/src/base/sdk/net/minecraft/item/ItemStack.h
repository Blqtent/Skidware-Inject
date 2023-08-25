#pragma once
#include "../../../Object.h"
#include "ItemArmor.h"
#include "../block/Block.h"
#include "item.h"
class CItemStack : public Object
{
	//CItemStack();

	//CItemStack(jobject instance);
	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	CItem GetItem();
	
	float GetStrVsBlock(CBlock block);
};