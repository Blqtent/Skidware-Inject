#pragma once

#include "../../../java/IClass.h"

struct CTimer : IClass
{
	CTimer();

	jclass GetClass();
	jobject GetInstance();

	float GetTimerSpeed();

	void SetTimerSpeed(float speed);

	float GetRenderPartialTicks();
};

