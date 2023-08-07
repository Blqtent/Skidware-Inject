#pragma once

#include "../../../../java/IClass.h"
#include "../../entity/player/EntityPlayer.h"
#include "../../../../../util/math/geometry.h"

#include <vector>

struct CChunk : IClass
{
	CChunk(jobject);

	jclass GetClass() { return this->Class; };
	jobject GetInstance() {return this->Instance;};
	
	jobject getBlock(jint x, jint y, jint z);
};

