#include "FloatBuffer.h"

#include "../../../java/java.h"
#include "../../../util/logger.h"

#include <vector>

FloatBuffer::FloatBuffer(jobject obj)
{
	if (obj == nullptr)
	{
		return;
	}
	this->Instance = obj;
	this->Class = Java::Env->FindClass("java/nio/FloatBuffer");
	if (this->Class == nullptr)
	{
		this->Class = Java::Env->GetObjectClass(this->Instance);
	}
	this->MethodIDs["get"] = Java::Env->GetMethodID(this->Class, "get", "(I)F");
}

Matrix FloatBuffer::GetMatrix()
{

	if (this->GetClass() == nullptr)
	{
		return Matrix{};
	}
	if (this->GetInstance() == nullptr)
	{
		return Matrix{};
	}
	std::vector<float> arr;
	for (int i = 0; i < 16; i++)
	{
		// I think we should cache it.(class and methodID.but i am lazzzzyyy)
		if (this->MethodIDs["get"] == nullptr)
		{
			this->MethodIDs["get"] = Java::Env->GetMethodID(this->Class, "get", "(I)F");
			if (this->MethodIDs["get"] == nullptr)
				return Matrix{};
			
		}
		arr.push_back(Java::Env->CallFloatMethod(this->GetInstance(), this->MethodIDs["get"], i));
	}

	Matrix m;

	m.m00 = arr[0];
	m.m01 = arr[1];
	m.m02 = arr[2];
	m.m03 = arr[3];
	m.m10 = arr[4];
	m.m11 = arr[5];
	m.m12 = arr[6];
	m.m13 = arr[7];
	m.m20 = arr[8];
	m.m21 = arr[9];
	m.m22 = arr[10];
	m.m23 = arr[11];
	m.m30 = arr[12];
	m.m31 = arr[13];
	m.m32 = arr[14];
	m.m33 = arr[15];

	return m;
}


jclass FloatBuffer::GetClass()
{
	return this->Class;
}

jobject FloatBuffer::GetInstance()
{
	return this->Instance;
}