#pragma once

#include "../../../../Object.h"
#include "../../entity/player/EntityPlayer.h"
#include "../../../../../util/math/geometry.h"

#include <vector>

class CChunk : public Object
{
	//CChunk(jobject);

	//jclass getClass() { return this->Class; };
	//jobject getInstance() {return this->Instance;};
	//
public:
	using Object::Object;
	jobject getBlock(jint x, jint y, jint z);
};

