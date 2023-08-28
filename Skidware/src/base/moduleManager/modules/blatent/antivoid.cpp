#include "antivoid.h"
#include "../../../menu/menu.h"


Antivoid::Antivoid() : AbstractModule("Antivoid", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Antivoid* Antivoid::getInstance() {
	static auto* inst = new Antivoid();
	//Logger::Log("Antivoid");
	return inst;
}

void Antivoid::onDisable() {
}

void Antivoid::onEnable() {
}

void Antivoid::onUpdate(const EventUpdate e)
{

	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (!this->getToggle()) {
		return;
	}
	if (getMode() == 0) {
		if (SDK::Minecraft->thePlayer->fallDistance() > 4) {
			SDK::Minecraft->thePlayer->setMotion(Vector3(SDK::Minecraft->thePlayer->getMotion().x, 1, SDK::Minecraft->thePlayer->getMotion().z));
		}
	}
}


void Antivoid::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Antivoid", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(34565464, "Toggle Antivoid", this);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &this->antikick);

		ImGui::Text("Antivoid Mode");
		ImGui::Combo("Antivoid Mode", &this->getMode(), this->modes, 1);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
