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

#include "modules/blatent/killaura.h"
#include "modules/blatent/speed.h"
#include "modules/player/blink.h"
#include "modules/blatent/nofall.h"
#include "modules/blatent/flight.h"
#include "modules/blatent/longjump.h"
//#include "../extension/scripting.hpp"

//#include "../moduleManager/modules/player/autotool.h"

#include <Windows.h>
#include "modules/visual/fullbright.h"
void ModuleManager::Init()
{
}

void ModuleManager::UpdateModules()
{
	if (!CommonData::SanityCheck()) return;

	CommonData::UpdateData();
	Esp::Update();
	Fulbright::Update();

	AimAssist::Update();
	Reach::Update();
	Velocity::Update();

	LeftAutoClicker::Update();
	RightAutoClicker::Update();
	//Blink::Update();
	Fastplace::Update();
	Eagle::Update();
	Killaura::Update();	
	Speed::Update();

	Nofall::Update();
	Flight::Update();
	LongJump::Update();
	
}
