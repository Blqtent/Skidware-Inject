#include "flight.h"
#include "../../../menu/menu.h"


//void Flight::Update()
//{
//	if (Menu::Open) return;
//	if (!CommonData::getInstance()->SanityCheck()) return;
//	if (!Enabled) {
//		return;
//	}
//
//	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
//	if (mode == 0) {
//		p->setMotion(Vector3(100000000000, 0, 100000000000));
//	}
//	else if (mode == 1) {
//		p->setOnGround(true);
//	}
//
//}
//
//void Flight::RenderMenu()
//{
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
//
//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
//	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
//
//	if (ImGui::BeginChild("Flight", ImVec2(450, 100))) {
//
//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
//		Menu::DoToggleButtonStuff(235354, "Toggle Flight", &Flight::Enabled);
//		if (mode == 11000)
//			Menu::DoSliderStuff(9864, "Glide Speed", &Flight::glideSpeed, -1, 1);
//		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);
//
//		ImGui::Text("Flight Mode");
//		ImGui::Combo("Flight Mode", &Flight::mode, Flight::modes, 2);
//
//		ImGui::EndChild();
//	}
//	ImGui::PopStyleVar();
//	ImGui::PopStyleColor();
//}
//Flight::Flight() : AbstractModule("Sprint", Category::MOVEMENT, 'R') {
//    EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
//    //EventManager::getInstance().reg(Events::EventUpdate, [this] { onUpdate(); });
//}

Flight::Flight() : AbstractModule("Flight", Category::BLATENT, 'U') {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Flight* Flight::getInstance() {
    static auto* inst = new Flight();
    return inst;
}



void Flight::onDisable() {
	//if (CommonData::getInstance()->SanityCheck())
		//SDK::Minecraft->thePlayer->setFly(false);

}

void Flight::onEnable() {
}

void Flight::onUpdate(const EventUpdate e) {
    if (!this->getToggle())return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	if (this->getMode() == 0) {
		p->set_speed(glideSpeed);

		p->setMotion(Vector3(p->getMotion().x, 0, p->getMotion().z));
	}
	else if (this->getMode() == 1) {
		if (p->getMotion().y < 0)
			p->setOnGround(true);
	}
	else if (this->getMode() == 2) {
		p->set_speed(glideSpeed);

		p->setMotion(Vector3(p->getMotion().x, 0, p->getMotion().z));

		if (!(p->getMoveForward() != 0 || p->getMoveStrafe() != 0)) {
			p->setMotion(Vector3(0, 0, 0));
		}

		if (GetAsyncKeyState(VK_LSHIFT)) {
			p->setMotion(Vector3(p->getMotion().x, -0.45, p->getMotion().z));
		}
		if (GetAsyncKeyState(VK_SPACE)) {
			p->setMotion(Vector3(p->getMotion().x, 0.45, p->getMotion().z));
		}
	}

}

void Flight::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Flight", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		Menu::DoToggleButtonStuff(235354, "Toggle Flight",this);
		if (getMode() == 0 || getMode() == 2)
			Menu::DoSliderStuff(9864, "Speed", &this->glideSpeed, 0, 5);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);

		ImGui::Text("Flight Mode");
		ImGui::Combo("Flight Mode", &Flight::getMode(), Flight::modes, 3);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}