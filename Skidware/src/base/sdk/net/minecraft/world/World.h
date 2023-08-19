#pragma once

#include "../../../Object.h"
#include "../entity/player/EntityPlayer.h"
#include "../../../../util/math/geometry.h"
#include "chunk/Chunk.h"
#include <vector>
#include "../../../java/util/List.h"

class CWorld : public Object
{
public:
	using Object::Object;
	List GetPlayerList();

	Vector3 rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock);

	CChunk getChunkFromChunkCoords(jint chunkX, jint chunkZ);

	bool isAirBlock(double x, double y, double z);
};

