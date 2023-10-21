#include "noslow.h"
#include "../../../menu/menu.h"
long count = 0;
bool isCurrMov() {
	if (!CommonData::getInstance()->SanityCheck()) return NULL;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;

	return (p->getMoveForward() != 0 || p->getMoveStrafe() != 0);
}

Noslowdown::Noslowdown() : AbstractModule("Noslowdown", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Noslowdown* Noslowdown::getInstance()
{
	static Noslowdown* inst = new Noslowdown();
	//Logger::Log("Antivoid");
	return inst;
}

void Noslowdown::onEnable()
{
}

void Noslowdown::onDisable()
{
	if (CommonData::getInstance()->SanityCheck()) {
		SDK::Minecraft->timer->SetTimerSpeed(1);

	}
}

void Noslowdown::onUpdate(EventUpdate e)
{
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (!this->getToggle()) {
		return;
	}
	if (SDK::Minecraft->thePlayer->isBlocking()) {
		//if (!((GetAsyncKeyState('W') & 1) || (GetAsyncKeyState('A') & 1) || (GetAsyncKeyState('D') & 1) || (GetAsyncKeyState('S') & 1))) return;
		if (!isCurrMov()) return;
		if (this->getMode() == 0) {
			SDK::Minecraft->thePlayer->set_speed(0.225);
			SDK::Minecraft->thePlayer->setSprint(true);
		}
		else if (this->getMode() == 1 && SDK::Minecraft->thePlayer->isOnGround() && (count % 3 == 0)) {
			SDK::Minecraft->thePlayer->set_speed(0.245);
			SDK::Minecraft->timer->SetTimerSpeed(0.96);
			SDK::Minecraft->thePlayer->setSprint(true);
		}
		else if (this->getMode() == 1 && SDK::Minecraft->thePlayer->isOnGround() && !(count % 3 == 0)) {
			SDK::Minecraft->thePlayer->set_speed(0.090);
			SDK::Minecraft->timer->SetTimerSpeed(1);
			SDK::Minecraft->thePlayer->setSprint(true);

		}

		count++;
	}
}

void Noslowdown::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Noslowdown", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(34565464, "Toggle Noslowdown", this);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &this->antikick);

		ImGui::Text("Noslowdown Mode");
		ImGui::Combo("Noslowdown Mode", &this->getMode(), this->modes, 2);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
