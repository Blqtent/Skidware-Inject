#include "Timer.h"

#include "../../../../java/java.h"
#include "../../../sdk.h"

CTimer::CTimer()
{
	Java::AssignClass("net.minecraft.util.Timer", this->Class);
	if (this->Class == nullptr)
	{
		if (!StrayCache::initialized) StrayCache::Initialize();
		this->Class = StrayCache::timer_class;
	}
	if (JNIHelper::IsForge()) {
		this->FieldIDs["renderPartialTicks"] = Java::Env->GetFieldID(this->Class, "field_74281_c", "F");
		this->FieldIDs["timerSpeed"] = Java::Env->GetFieldID(this->Class, "field_74278_d", "F");
		return;
	}
	this->FieldIDs["renderPartialTicks"] = Java::Env->GetFieldID(this->Class, "renderPartialTicks", "F");
	this->FieldIDs["timerSpeed"] = Java::Env->GetFieldID(this->Class, "timerSpeed", "F");

}

float CTimer::GetRenderPartialTicks()
{
	return Java::Env->GetFloatField(this->GetInstance(), this->FieldIDs["renderPartialTicks"]);
}

jclass CTimer::GetClass()
{
	return this->Class;
}

jobject CTimer::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["timer"]);
}

float CTimer::GetTimerSpeed()
{
	return Java::Env->GetFloatField(GetInstance(), this->FieldIDs["timerSpeed"]);

}

void CTimer::SetTimerSpeed(float speed)
{
	return Java::Env->SetFloatField(GetInstance(), this->FieldIDs["timerSpeed"], speed);

}