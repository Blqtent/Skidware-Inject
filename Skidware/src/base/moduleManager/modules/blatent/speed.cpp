#include "speed.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../player/fastplace.h"
#include "../../../menu/menu.h"
#include "../../../java/java.h"
#include <windows.h>
#include <numbers>
//#include "../../../extension/scripting.hpp"

Speed::Speed() : AbstractModule("Speed", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Speed* Speed::getInstance() {
	static auto* inst = new Speed();
	return inst;
}

void Speed::onDisable() {
}

void Speed::onEnable() {
}

static uint64_t timer = GetTickCount64();

bool isMoving() {
	if (!CommonData::getInstance()->SanityCheck()) return NULL;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;

	return (p->getMoveForward() != 0 || p->getMoveStrafe() != 0);
}

void Speed::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	//if (!SDK::Minecraft->thePlayer->isOnGround()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	
	if (getMode() == 0) {
		if (isMoving()) {
			p->set_speed(speed);
		}
		else {
			p->setMotion(Vector3(0, 100000000000, 0));
		}
		if (isMoving() && p->isOnGround()) {
			p->jump();
		}
	}
	else if (getMode() == 1) {
		if (p->isOnGround() && (p->getMoveForward() != 0 || p->getMoveStrafe() != 0) && GetTickCount64() - timer > 300) {
			timer = GetTickCount64();
			p->jump();
		}
	} 
	else if (getMode() == 2) {
		if (p->isOnGround()) {
			if (isMoving()) {

				p->set_speed(speed);
			}
			else {
				p->setMotion(Vector3(0, 100000000000, 0));
			}
		}
	}
	else if (getMode() == 3) {
		if (p->isOnGround()) {
			if (isMoving()) {
				p->set_speed(speed);
				p->setMotion(Vector3(100000000000, 0.2, 100000000000));

			}
			else {
				p->setMotion(Vector3(0, 100000000000, 0));
			}
		}
/*		else {
			Vector3 motion = p->getMotion();
			Vector3 speedMotion = Vector3(motion.x, motion.y - 0.27, motion.z);
			p->setMotion(speedMotion);
		}*/
	}

}

void Speed::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Strafe", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Strafe", this);
		if (this->getMode() == 0 || getMode() == 2 || getMode() == 3);
			Menu::DoSliderStuff(1734563, "Speed", &this->speed, 0, 3);
		if (this->getMode() == 2 || getMode() == 3)
			Menu::DoSliderStuff(11111, "Max Ground Speed", &this->maxspeed, 0, 3);
		ImGui::Text("Speed Mode Mode");
		ImGui::Combo("Mode", &this->getMode(), modes, 4);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
 