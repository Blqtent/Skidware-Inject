#pragma once

#include "../../../java/IClass.h"
#include "../entity/player/EntityPlayer.h"
#include "../../../../util/math/geometry.h"
#include "chunk/Chunk.h"
#include <vector>

struct CWorld : IClass
{
	CWorld();

	jclass GetClass();
	jobject GetInstance();

	std::vector<CEntityPlayer> GetPlayerList();

	Vector3 rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock);

	CChunk getChunkFromChunkCoords(jint chunkX, jint chunkZ);

	bool isAirBlock(double x, double y, double z);
};

