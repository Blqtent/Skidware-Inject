#pragma once
#include "../../../java/IClass.h"

struct CItem : IClass
{
	CItem();

	CItem(jobject instance);
	jclass GetClass();
	jobject GetInstance();
};