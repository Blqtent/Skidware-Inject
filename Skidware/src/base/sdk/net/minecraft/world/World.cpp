#include "World.h"

#include "../../../sdk.h"
#include "../../../../java/java.h"
#include "../../../java/util/List.h"
#include "../util/Vec3.h"
#include "../util/MovingObjectPosition.h"

#include "../../../../util/logger.h"

CWorld::CWorld() 
{
	Java::AssignClass("net.minecraft.world.World", this->Class);
	if (this->Class == nullptr)
	{
		if (!StrayCache::initialized) StrayCache::Initialize();
		this->Class = StrayCache::world_class;
	}
	if (JNIHelper::IsForge()) {
		this->FieldIDs["playerEntities"] = Java::Env->GetFieldID(this->Class, "field_73010_i", "Ljava/util/List;");

		this->MethodIDs["rayTraceBlocks"] = Java::Env->GetMethodID(this->Class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");

		this->MethodIDs["isAirBlock"] = Java::Env->GetMethodID(this->Class, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
		this->MethodIDs["getChunkFromChunkCoords"] = Java::Env->GetMethodID(this->Class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");
		return;
	}

	this->FieldIDs["playerEntities"] = Java::Env->GetFieldID(this->Class, "playerEntities", "Ljava/util/List;");

	this->MethodIDs["rayTraceBlocks"] = Java::Env->GetMethodID(this->Class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");

	this->MethodIDs["getChunkFromChunkCoords"] = Java::Env->GetMethodID(this->Class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");
	this->MethodIDs["isAirBlock"] = Java::Env->GetMethodID(this->Class, "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");
}

jclass CWorld::GetClass()
{
	return this->Class;
}

jobject CWorld::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["theWorld"]);
}

std::vector<CEntityPlayer> CWorld::GetPlayerList()
{
	std::vector<CEntityPlayer> finalList;
	if (this->GetInstance() == nullptr)
	{
		return std::vector<CEntityPlayer>{};
	}
	jobject playerEntitiesObj = Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["playerEntities"]);

	if (playerEntitiesObj == nullptr)
	{
		return std::vector<CEntityPlayer>{};
	}

	List playerEntitiesList =  List::List(playerEntitiesObj);
	if (playerEntitiesList.GetClass() == nullptr)
	{
		return std::vector<CEntityPlayer>{};
	}
	jobjectArray playerEntities = playerEntitiesList.toArray();

	if (playerEntities == nullptr)
	{
		return std::vector<CEntityPlayer>{};
	}
	int size = Java::Env->GetArrayLength(playerEntities);
	
	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::Env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntityPlayer player =  CEntityPlayer::CEntityPlayer(obj_player);
		finalList.push_back(player);
	}

	Java::Env->DeleteLocalRef(playerEntitiesObj);
	Java::Env->DeleteLocalRef(playerEntities);

	return finalList;
}

Vector3 CWorld::rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock)
{
	// SPECIAL CASE
	jclass cls;
	Java::AssignClass("net.minecraft.util.Vec3", cls);
	jmethodID init = Java::Env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = Java::Env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = Java::Env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	jobject movingObjPos_j = Java::Env->CallObjectMethod(
		this->GetInstance(),
		this->MethodIDs["rayTraceBlocks"],
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
	return CChunk(Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getChunkFromChunkCoords"]));
}

bool CWorld::isAirBlock(double x, double y, double z)
{
	/*
	if (JNIHelper::IsVanilla()) {
		jclass bpclass = Java::Env->FindClass("cj");
		jmethodID bpmid = Java::Env->GetMethodID(bpclass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(bpclass, bpmid, (jdouble)x, (jdouble)y, (jdouble)z);

		jclass wclass = Java::Env->GetObjectClass(this->GetInstance());
		jmethodID mid = Java::Env->GetMethodID(wclass, "d", "(Lcj;)Z");

		bool res = Java::Env->CallBooleanMethod(this->GetInstance(), mid, blockpos);

		Java::Env->DeleteLocalRef(bpclass);
		Java::Env->DeleteLocalRef(wclass);
		Java::Env->DeleteLocalRef(blockpos);

		return res;
	}
	*/
	if (JNIHelper::IsForge()) {
		jclass blockPosClass;
		Java::AssignClass("net.minecraft.util.BlockPos", blockPosClass);
		jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

		return Java::Env->CallBooleanMethod(this->GetInstance(), this->MethodIDs["isAirBlock"], blockpos);

	}
	jclass blockPosClass;
	Java::AssignClass("net.minecraft.util.BlockPos", blockPosClass);
	jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

	return Java::Env->CallBooleanMethod(this->GetInstance(), this->MethodIDs["isAirBlock"], blockpos);
}
