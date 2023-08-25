#include "World.h"

#include "../../../sdk.h"
#include "../../../../java/java.h"

#include "../util/Vec3.h"
#include "../util/MovingObjectPosition.h"

#include "../../../../util/logger.h"



//CWorld::CWorld() 
//{
//	Java::AssignClass("net.minecraft.world.World", StrayCache::world_class);
//	if (StrayCache::world_class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		StrayCache::world_class = StrayCache::world_class;
//	}
//	if (JNIHelper::IsForge()) {
//		world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "field_73010_i", "Ljava/util/List;");
//
//		world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
//
//		world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
//		world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");
//		return;
//	}
//
//	world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "playerEntities", "Ljava/util/List;");
//
//	world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
//
//	world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");
//	world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");
//}
//
//jclass CWorld::getClass()
//{
//	return StrayCache::world_class;
//}
//
//jobject CWorld::getInstance()
//{
//	return Java::Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["theWorld);
//}

List CWorld::GetPlayerList()
{
	//std::vector<CEntityPlayer> finalList;
	//if (this->getInstance() == nullptr)
	//{
	//	return std::vector<CEntityPlayer>{};
	//}
	//jobject playerEntitiesObj = Java::Env->GetObjectField(this->getInstance(), StrayCache::world_playerEntities);

	//if (playerEntitiesObj == nullptr)
	//{
	//	return std::vector<CEntityPlayer>{};
	//}

	//List playerEntitiesList =  List::List(playerEntitiesObj);
	//if (playerEntitiesList.getClass() == nullptr)
	//{
	//	return std::vector<CEntityPlayer>{};
	//}
	//jobjectArray playerEntities = playerEntitiesList.toArray();

	//if (playerEntities == nullptr)
	//{
	//	return std::vector<CEntityPlayer>{};
	//}
	//int size = Java::Env->GetArrayLength(playerEntities);
	//
	//for (int i = 0; i < size; i++)
	//{
	//	jobject obj_player = Java::Env->GetObjectArrayElement(playerEntities, i);
	//	if (!obj_player) continue;

	//	CEntityPlayer player =  CEntityPlayer::CEntityPlayer(obj_player);
	//	finalList.push_back(player);
	//}

	//Java::Env->DeleteLocalRef(playerEntitiesObj);
	//Java::Env->DeleteLocalRef(playerEntities);

	return List(Java::Env->GetObjectField(instance, StrayCache::world_playerEntities));
}

Vector3 CWorld::rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock)
{
	// SPECIAL CASE
	jclass cls = StrayCache::vec3_class;
	jmethodID init = Java::Env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = Java::Env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = Java::Env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	jobject movingObjPos_j = Java::Env->CallObjectMethod(
		this->getInstance(),
		StrayCache::world_rayTraceBlocks,
		j_from,
		j_to,
		stopOnLiquid,
		ignoreBlockWithoutBoundingBox,
		returnLastUncollidableBlock
	);

	if (movingObjPos_j == NULL) {
		Java::Env->DeleteLocalRef(j_to);
		Java::Env->DeleteLocalRef(j_from);
		Java::Env->DeleteLocalRef(cls);
		return Vector3(0,0,0);
	}

	CMovingObjectPosition movingObjPos = CMovingObjectPosition(movingObjPos_j);
	CVec3 a = movingObjPos.GetBlockPosition();
	Vector3 blockPos = a.GetNativeVector3();
	Java::Env->DeleteLocalRef(j_to);
	Java::Env->DeleteLocalRef(j_from);
	Java::Env->DeleteLocalRef(cls);
	return blockPos;
}

CChunk CWorld::getChunkFromChunkCoords(jint chunkX, jint chunkZ)
{
	return CChunk(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::world_getChunkFromChunkCoords));
}

CIBlockState CWorld::getBlockState(BlockPos pos) {
	//if (!this->isValid() || this->isNULL()) 
	//{
	//	Logger::Log("e");
	//	return CBlockState{};
	//}
	//
	return CIBlockState(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::world_getBlockState, pos.getInstance()));
}

bool CWorld::isAirBlock(double x, double y, double z)
{
	/*
	if (JNIHelper::IsVanilla()) {
		jclass bpclass = Java::Env->FindClass("cj");
		jmethodID bpmid = Java::Env->GetMethodID(bpclass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(bpclass, bpmid, (jdouble)x, (jdouble)y, (jdouble)z);

		jclass wclass = Java::Env->GetObjectClass(this->getInstance());
		jmethodID mid = Java::Env->GetMethodID(wclass, "d", "(Lcj;)Z");

		bool res = Java::Env->CallBooleanMethod(this->getInstance(), mid, blockpos);

		Java::Env->DeleteLocalRef(bpclass);
		Java::Env->DeleteLocalRef(wclass);
		Java::Env->DeleteLocalRef(blockpos);

		return res;
	}
	*/
	if (JNIHelper::IsForge()) {
		jclass blockPosClass = StrayCache::blockPos_class;
		jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

		return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos);

	}
	jclass blockPosClass = StrayCache::blockPos_class;
	jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos);
}

bool CWorld::isAirBlock(BlockPos pos)
{
	/*
	if (JNIHelper::IsVanilla()) {
		jclass bpclass = Java::Env->FindClass("cj");
		jmethodID bpmid = Java::Env->GetMethodID(bpclass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(bpclass, bpmid, (jdouble)x, (jdouble)y, (jdouble)z);

		jclass wclass = Java::Env->GetObjectClass(this->getInstance());
		jmethodID mid = Java::Env->GetMethodID(wclass, "d", "(Lcj;)Z");

		bool res = Java::Env->CallBooleanMethod(this->getInstance(), mid, blockpos);

		Java::Env->DeleteLocalRef(bpclass);
		Java::Env->DeleteLocalRef(wclass);
		Java::Env->DeleteLocalRef(blockpos);

		return res;
	}
	*/
	if (JNIHelper::IsForge()) {
		return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());

	}
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());
}
