#include "Chunk.h"

CChunk::CChunk(jobject instance)
{
	Java::AssignClass("net.minecraft.world.chunk.Chunk", this->Class);

	if (JNIHelper::IsForge()) {

		this->MethodIDs["getBlock"] = Java::Env->GetMethodID(this->Class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
		return;
	}

	
	this->MethodIDs["getBlock"] = Java::Env->GetMethodID(this->Class, "getBlock", "(III)Lnet/minecraft/block/Block;");
	
	this->Instance = instance;
}

jobject CChunk::getBlock(jint x, jint y, jint z)
{
	return Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getBlock"], x, y, z);
}
