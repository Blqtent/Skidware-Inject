#include "base.h"
#include "sdk/sdk.h"

#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/combat/aimAssist.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/clicker/leftAutoClicker.h"
#include "moduleManager/modules/clicker/rightAutoClicker.h"
#include "moduleManager/modules/player/eagle.h"
#include "moduleManager/modules/player/fastplace.h"
#include "moduleManager/modules/combat/velocity.h"
#include "moduleManager/modules/blatent/killaura.h"
#include "moduleManager/modules/blatent/flight.h"
#include "moduleManager/modules/blatent/speed.h"
#include "moduleManager/modules/player/blink.h"
#include "moduleManager/modules/visual/cavefinder.h"
#include "moduleManager/modules/visual/fullbright.h"
#include "moduleManager/modules/blatent/nofall.h"
#include "moduleManager/modules/blatent/timerhack.h"
#include <cmath>
#include "moduleManager/modules/player/blink.h"
//#include "extension/scripting.hpp"

#include "menu/menu.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/combat/teams.h"
#include "moduleManager/modules/blatent/longjump.h"
#include "moduleManager/ModuleManager.h"
#include "moduleManager/modules/blatent/tower.h"
#include "moduleManager/modules/player/autotool.h"
#include "moduleManager/modules/blatent/antivoid.h"
#include "moduleManager/modules/blatent/noslow.h"

void Base::RenderLoop()
{
	if (!Base::Running) return;

	float font_size = 20 * 2;
	//ImU32 color = ImGui::GetColorU32(ImGuiCol_CheckMark);
	//ImU32 secRectColor = ImGui::GetColorU32(ImGuiCol_Border, 2.1f);

	int secRectDistance = 4 * 2;
	int DistanceToEnd = 10 * 2;
	ImU32 secRectColor = Menu::watermarkColor;
	ImU32 color = ImGui::GetColorU32(ImGuiCol_Text);

	int moduleIndexY = 0 * 2;
		
	ImGui::GetWindowDrawList()->AddText(Menu::BiggerFont, font_size * 1.5, ImVec2(7, 2), secRectColor, "Skidware");

	moduleIndexY = 24 * 2;
	ImColor rectColor = ImColor(0.0f, 0.0f, 0.0f, 0.35f);

	Esp::getInstance()->RenderUpdate();
	AimAssist::getInstance()->RenderUpdate();

	if (LongJump::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  LongJump").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  LongJump");
		moduleIndexY += 18 * 2;
	}

	if (AimAssist::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
			int yy = moduleIndexY + 18 * 2;
			int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  AimAssist").x + DistanceToEnd;
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  AimAssist");
		moduleIndexY += 18 * 2;
	}

	if (AutoTool::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  AutoTool").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  AutoTool");
		moduleIndexY += 18 * 2;
	}

	if (Killaura::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  KillAura").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  KillAura");
		moduleIndexY += 18 * 2;
	}

	if (Tower::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Scaffold").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Scaffold");
		moduleIndexY += 18 * 2;
	}

	if (Velocity::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Velocity").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Velocity");
		moduleIndexY += 18 * 2;
	}

	if (Antibot::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  AntiBot").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  AntiBot");
		moduleIndexY += 18 * 2;
	}

	if (LeftAutoClicker::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
			int yy = moduleIndexY + 18 * 2;
			int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Clicker").x + DistanceToEnd;
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Clicker");
		moduleIndexY += 18 * 2;
	}

	if (Nofall::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  NoFall").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  NoFall");
		moduleIndexY += 18 * 2;
	}

	if (Reach::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Reach").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Reach");
		moduleIndexY += 18 * 2;
	}

	if (Flight::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Flight").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Flight");
		moduleIndexY += 18 * 2;
	}

	if (Eagle::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Eagle").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Eagle");
		moduleIndexY += 18 * 2;
	}

	if (Blink::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
		int yy = moduleIndexY + 18 * 2;
		int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  Blink").x + DistanceToEnd;
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  Blink");
		moduleIndexY += 18 * 2;
	}

	if (Esp::getInstance()->getToggle()) {
		//if (TextGui::rectangles) {
			int yy = moduleIndexY + 18 * 2;
			int vecLength = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, "  ESP").x + DistanceToEnd;
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(vecLength, yy + 6 * 2), rectColor);
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(7, yy - (font_size / 2) - 2 * 2), ImVec2(7 + secRectDistance, yy + 6 * 2), secRectColor);
		//}

		ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(4, moduleIndexY + 4), color, "  ESP");
		moduleIndexY += 18 * 2;
	}
}

/*extern ImVec4 clear_col;
static int y;
void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running) return;
	const char* watermark = "Skidware By Smellon and Blqtent";
	// goofy ahh css
	float margin = 3;
	float font_size = 24;
	int m_iOffset = 0;

	ImVec2 screenSize = ImGui::GetWindowSize();
	ImVec2 textSize = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermark);
	float posX = screenSize.x - textSize.x - margin;
	float posY = screenSize.y - textSize.y - margin;
	
	Esp::getInstance()->RenderUpdate();
	AimAssist::getInstance()->RenderUpdate();
	//Blink::getInstance()->RenderUpdate();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImDrawList* d = ImGui::GetWindowDrawList();

	ImU32 watermarkCol = Menu::watermarkColor;

	d->AddText(Menu::Font, font_size, ImVec2(4, 4), watermarkCol, "Skidware V1.09");

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.IniFilename = NULL; // GET RID OF IMGUI.INI
	
	y = 24;

	//else {
		if (AimAssist::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Aimassist");
			y += 20;
		}
		if (Esp::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "ESP");
			y += 20;
		}
		if (LeftAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LeftClicker");
			y += 20;
		}
		if (RightAutoClicker::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "RightClicker");
			y += 20;
		}
		if (Reach::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Reach");
			y += 20;
		}
		if (Velocity::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Velocity");
			y += 20;
		}
		if (Eagle::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Eagle");
			y += 20;
		}
		if (Fastplace::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "FastPlace");
			y += 20;
		}
		if (AutoTool::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "AutoTool");
			y += 20;
		}
		if (Cavefinder::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "XRay");
			y += 20;
		}
		if (Antibot::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Antibot");
			y += 20;
		}

		//if (Teams::getInstance()->getToggle()) {
			//d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Teams");
			//y += 20;
		//}

		if (Killaura::getInstance()->getToggle()) {
			if (Killaura::getInstance()->getMode() == 0) {
				d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Legit");
			}
			else if (Killaura::getInstance()->getMode() == 1) {
				d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Normal");
			}
			else if (Killaura::getInstance()->getMode() == 2) {
				d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Killaura - Silent");
			}
			y += 20;
		}
		if (TimerHack::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Timer");
			y += 20;
		}
		if (Fulbright::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fulbright");
			y += 20;

		}
		if (Speed::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Speed");
			y += 20;
		}
		if (Nofall::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Nofall");
			y += 20;
		}
		if (Flight::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Flight");
			y += 20;
		}
		if (Tower::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Scaffold");
			y += 20;
		}

		if (LongJump::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "LongJump");
			y += 20;
		}
		if (Blink::getInstance()->getToggle()) {
			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Fakelag");
			y += 20;
		}
		//Logger::Log("Antivoid 3 2");

		if (Antivoid::getInstance()->getToggle()) {
			//Logger::Log("Antivoid 3");

			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Antivoid");
			y += 20;
		}
		if (Noslowdown::getInstance()->getToggle()) {
			//Logger::Log("Antivoid 3");

			d->AddText(Menu::Font, font_size, ImVec2(4, y), ImColor(255, 255, 255), "Noslowdown");
			y += 20;
		}

	//}
}*/