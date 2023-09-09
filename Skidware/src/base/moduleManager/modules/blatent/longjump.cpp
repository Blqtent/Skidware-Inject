#include "longjump.h"
#include "../../../menu/menu.h"


LongJump::LongJump() : AbstractModule("LongJump", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

LongJump* LongJump::getInstance() {
	static auto* inst = new LongJump();
	return inst;
}

void LongJump::onDisable() {
}

void LongJump::onEnable() {
}

void LongJump::onUpdate(const EventUpdate e)
{

	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (!this->getToggle()) {
		return;
	}
	if (getMode() == 0) {
		if (SDK::Minecraft->thePlayer->getHurtTime() > 0) {
			SDK::Minecraft->thePlayer->set_speed(speed);
			if (SDK::Minecraft->thePlayer->isOnGround())
				SDK::Minecraft->thePlayer->jump();

		}
	}
	if (getMode() == 1) {
		SDK::Minecraft->thePlayer->setMotion(Vector3(SDK::Minecraft->thePlayer->getMotion().x, SDK::Minecraft->thePlayer->getMotion().x + 0.05999, SDK::Minecraft->thePlayer->getMotion().z));
		SDK::Minecraft->thePlayer->set_speed(SDK::Minecraft->thePlayer->get_speed() * 1.08f);

	}
}


void LongJump::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Longjump", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(34565464, "Toggle Longjump", this);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &this->antikick);

		ImGui::Text("Longjump Mode");
		ImGui::Combo("Longjump Mode", &this->getMode(), this->modes, 2);
		if (this->getMode() == 0)
			Menu::DoSliderStuff(69420666, "Longjump Speed", &this->speed, 0, 5);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
