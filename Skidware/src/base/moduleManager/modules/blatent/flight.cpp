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

Flight::Flight() : AbstractModule("Flight", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Flight* Flight::getInstance() {
    static auto* inst = new Flight();
    return inst;
}

void Flight::onDisable() {

}

void Flight::onEnable() {
}

void Flight::onUpdate(const EventUpdate e) {
    if (!this->getToggle())return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	if (this->getMode() == 0) {
		p->setMotion(Vector3(100000000000, 0, 100000000000));
	}
	else if (this->getMode() == 1) {
		p->setOnGround(true);
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
		if (getMode() == 11000)
			Menu::DoSliderStuff(9864, "Glide Speed", &this->glideSpeed, -1, 1);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);

		ImGui::Text("Flight Mode");
		ImGui::Combo("Flight Mode", &Flight::getMode(), Flight::modes, 2);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}