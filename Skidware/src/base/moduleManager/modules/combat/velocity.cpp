#include "velocity.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"

Velocity::Velocity() : AbstractModule("Velocity", Category::COMBAT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Velocity* Velocity::getInstance() {
	static auto* inst = new Velocity();
	return inst;
}

void Velocity::onDisable() {
}

void Velocity::onEnable() {
}



int counter;
void Velocity::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
	//if (Menu::Open) return;
	if (this->getMode() == 0) {
		if (thePlayer->getHurtTime() > 3) {
			Vector3 motion = thePlayer->getMotion();
			motion.x = motion.x * Velocity::Horizontal;
			motion.y = motion.y * Velocity::Vertical;
			motion.z = motion.z * Velocity::Horizontal;


			thePlayer->setMotion(motion);
		}
	}
	else if (this->getMode() == 1) {
		if (thePlayer->getHurtTime() > 7 && thePlayer->isOnGround() && counter++ % 2 == 0) {
			POINT pos_cursor;
			GetCursorPos(&pos_cursor);
			thePlayer->jump();
		}
	}
	else if (this->getMode() == 2) {
		if (thePlayer->getHurtTime() > 5) {
			thePlayer->setOnGround(true);
		}
	}
	else if (this->getMode() == 3) {
		if (thePlayer->getHurtTime() > 5) {
			thePlayer->set_speed(thePlayer->get_speed());
		}
	}

}

void Velocity::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("velocity", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2134078, "Toggle Velocity", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(248913712347, "Horizontal", &this->Horizontal, 0.f, 1.f);
		Menu::DoSliderStuff(2489137, "Vertical", &this->Vertical, 0.f, 1.f);
		ImGui::Combo("Mode", &this->getMode(), this->modes, 4);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
