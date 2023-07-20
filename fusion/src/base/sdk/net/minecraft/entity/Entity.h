#pragma once

#include "../../../java/IClass.h"
#include "../../../../util/math/geometry.h"
#include "../util/AxisAlignedBB.h"

struct CEntity : IClass
{
	CEntity();

	CEntity(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	std::string GetName();

	Vector3 GetPos();
	Vector3 GetEyePos();
	Vector3 GetLastTickPos();

	void setMotion(Vector3 motion);

	Vector3 getMotion();

	bool isOnGround();
	float fallDistance();

	void setOnGround(bool state);

	bool IsSneaking();
	void setSneaking(bool state);

	float GetHeight();
	float GetWidth();

	float GetDistanceWalkedModified();
	float GetPrevDistanceWalkedModified();

	float GetRotationYaw();
	float GetRotationPitch();

	float GetPrevRotationYaw();
	float GetPrevRotationPitch();

	Vector2 GetAngles();
	Vector2 GetPrevAngles();

	void SetAngles(Vector2 angles);

	CAxisAlignedBB GetBB();
	void SetBB(BoundingBox bb);
};