#include "RenderManager.h"

#include "../../../../../../java/java.h"
#include "../../../../../sdk.h"

//CRenderManager::CRenderManager()
//{
//	Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
//
//	if (renderManager_class == nullptr)
//	{
//		if (!initialized) Initialize();
//		renderManager_class = renderManager_class;
//	}
//	/*
//	if (JNIHelper::IsVanilla()) {
//		renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "o", "D");
//		renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "p", "D");
//		renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "q", "D");
//
//		renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "h", "D");
//		renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "i", "D");
//		renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "j", "D");
//		return;
//	}
//	*/
//	if (JNIHelper::IsForge()) {
//		renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
//		renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
//		renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
//
//		renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
//		renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
//		renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
//		return;
//	}
//
//	renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "renderPosX", "D");
//	renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "renderPosY", "D");
//	renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "renderPosZ", "D");
//
//	renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "viewerPosX", "D");
//	renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "viewerPosY", "D");
//	renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "viewerPosZ", "D");
//}

Vector3 CRenderManager::RenderPos()
{
	//jobject instance = this->getInstance();
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosX),
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosY),
		(float)(double) Java::Env->GetDoubleField(instance, StrayCache::renderManager_renderPosZ)
	};
}

Vector3 CRenderManager::ViewerPos()
{
	//jobject instance = this->getInstance();
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosX),
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosY),
		(float)(double)Java::Env->GetDoubleField(instance, StrayCache::renderManager_viewerPosZ)
	};
}
