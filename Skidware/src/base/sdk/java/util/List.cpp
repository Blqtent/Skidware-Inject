#include "List.h"
#include "../../../java/java.h"

List::List(jobject jlist)
{
	if (jlist == nullptr)
	{
		return;
	}
	
	this->Class = Java::Env->FindClass("java/util/List");
	if (this->Class == nullptr)
	{
		return;
	}

	this->Instance = jlist;

	this->MethodIDs["toArray"] = Java::Env->GetMethodID(this->Class, "toArray", "()[Ljava/lang/Object;");
}

jclass List::GetClass()
{
	return this->Class;
}

jobject List::GetInstance()
{
	return this->Instance;
}

jobjectArray List::toArray()
{
	if (this->Instance == nullptr)
	{
		return NULL;
	}

	return (jobjectArray) Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["toArray"]);
}
