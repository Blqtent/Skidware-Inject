#pragma once

#include "../../../java/IClass.h"
#include "../../../../util/math/geometry.h"
#include "../../../strayCache.h"

struct BlockPos : IClass
{
	BlockPos();
	BlockPos(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	Vector3 getPos();
};