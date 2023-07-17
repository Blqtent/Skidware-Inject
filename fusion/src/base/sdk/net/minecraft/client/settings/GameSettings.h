#pragma once
#include "../../../../java/IClass.h"

struct CGameSettings : IClass
{
	CGameSettings();

	jclass GetClass();
	jobject GetInstance();

	int GetThirdPersonView();
	float GetFOV();
	void SetGamma(float gamma);
	float GetGamma();
	void SetFullscreenKeyToNull();
	void RestoreFullscreenKey();
};

