#include "JNIHelper.h"
#include <Windows.h>

bool JNIHelper::AlreadyCheckedForge = false;
bool JNIHelper::IsForgeExisting = false;

jclass JNIHelper::ForgeFindClass(const char* name)
{
	if (LaunchWrapperClassLoaderClass == NULL)
	{
		LaunchWrapperClassLoaderClass = Java::Env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
		if (LaunchWrapperClassLoaderClass == NULL) return NULL;
	}

	if (FindClassMethodID == NULL)
	{
		FindClassMethodID = Java::Env->GetMethodID(LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		if (FindClassMethodID == NULL) return NULL;
	}

	if (LaunchClass == NULL)
	{
		LaunchClass = Java::Env->FindClass("net/minecraft/launchwrapper/Launch");
		if (LaunchClass == NULL) return NULL;
	}

	if (ClassLoaderFieldID == NULL)
	{
		ClassLoaderFieldID = Java::Env->GetStaticFieldID(LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
		if (ClassLoaderFieldID == NULL) return NULL;
	}

	if (ClassLoaderObject == NULL)
	{
		ClassLoaderObject = Java::Env->GetStaticObjectField(LaunchClass, ClassLoaderFieldID);
		if (ClassLoaderObject == NULL) return NULL;
	}

	jstring jname = Java::Env->NewStringUTF(name);
	jclass cls = (jclass)Java::Env->CallObjectMethod(ClassLoaderObject, FindClassMethodID, jname);

	Java::Env->DeleteLocalRef(jname);

	return cls;
}

bool JNIHelper::IsForge()
{
	if (!AlreadyCheckedForge)
	{
		AlreadyCheckedForge = true;
		jclass forgeClass = Java::Env->FindClass("net/minecraftforge/common/ForgeVersion");
		if (forgeClass != NULL)
		{
			Java::Env->DeleteLocalRef(forgeClass);
			IsForgeExisting = true;
		}
	}
	return IsForgeExisting;
}

bool JNIHelper::IsVanilla()
{
	if (!IsForge() && FindWindowA(NULL, "Minecraft 1.8.9")) {
		return true;
	}
	return false;
}