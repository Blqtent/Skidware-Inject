#include "moduleManager.h"

#include "modules/visual/esp.h"
#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/clicker/leftAutoClicker.h"
#include "modules/clicker/rightAutoClicker.h"
#include "commonData.h"
#include "modules/combat/velocity.h"
#include "modules/player/fastplace.h"
#include "modules/player/eagle.h"
#include "modules/visual/Fullbright.h"
#include "modules/blatent/killaura.h"
#include "modules/blatent/Strafe.h"
#include "modules/player/blink.h"
#include "modules/blatent/nofall.h"
#include "../extension/scripting.hpp"

#include <Windows.h>
void ModuleManager::Init()
{
}

void ModuleManager::UpdateModules()
{
	if (!CommonData::SanityCheck()) return;

	CommonData::UpdateData();
	Esp::Update();

	AimAssist::Update();
	Reach::Update();
	Velocity::Update();

	LeftAutoClicker::Update();
	RightAutoClicker::Update();

	Fastplace::Update();
	Eagle::Update();
	Killaura::Update();	
	Strafe::Update();
	Blink::Update();

	Nofall::Update();
}
