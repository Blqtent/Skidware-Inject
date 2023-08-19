#include "ActiveRenderInfo.h"

#include "../../../../../java/java.h"
#include "../../../../sdk.h"
#include "../../../../java/nio/FloatBuffer.h"
#include "../../../../../util/logger.h"

//CActiveRenderInfo::CActiveRenderInfo()
//{
//	Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", this->Class);
//
//
//	if (this->Class == nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		this->Class = StrayCache::activeRenderInfo_class;
//	}
//
//
//
//	if (JNIHelper::IsVanilla()) {
//		this->FieldIDs["PROJECTION"] = Java::Env->GetStaticFieldID(this->Class, "c", "Ljava/nio/FloatBuffer;");
//		this->FieldIDs["MODELVIEW"] = Java::Env->GetStaticFieldID(this->Class, "b", "Ljava/nio/FloatBuffer;");
//		return;
//	}
//
//	if (JNIHelper::IsForge()) {
//		this->FieldIDs["PROJECTION"] = Java::Env->GetStaticFieldID(this->Class, "field_178813_c", "Ljava/nio/FloatBuffer;");
//		this->FieldIDs["MODELVIEW"] = Java::Env->GetStaticFieldID(this->Class, "field_178812_b", "Ljava/nio/FloatBuffer;");
//		return;
//	}
//
//	this->FieldIDs["PROJECTION"] = Java::Env->GetStaticFieldID(this->Class, "PROJECTION", "Ljava/nio/FloatBuffer;");
//	this->FieldIDs["MODELVIEW"] = Java::Env->GetStaticFieldID(this->Class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
//}

//jclass CActiveRenderInfo::getClass()
//{
//	return this->Class;
//}
//
//jobject CActiveRenderInfo::getInstance()
//{
//	return NULL;
//}

Matrix CActiveRenderInfo::ProjectionMatrix()
{
	jobject projection = Java::Env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_PROJECTION);
	Matrix m = FloatBuffer(projection).GetMatrix();
	return m;
}

Matrix CActiveRenderInfo::ModelViewMatrix()
{
	jobject modelView = Java::Env->GetStaticObjectField(StrayCache::activeRenderInfo_class, StrayCache::activeRenderInfo_MODELVIEW);
	Matrix m = FloatBuffer::FloatBuffer(modelView).GetMatrix();
	return m;
}

