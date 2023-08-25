#include "noslow.h"
#include "../../../menu/menu.h"

NoSlow::NoSlow() : AbstractModule("NoSlow", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}


NoSlow* NoSlow::getInstance()
{
	static auto* inst = new NoSlow();
	std::cout << "E\n";
	Sleep(1000);
	return inst;
}

void NoSlow::onEnable()
{
}

void NoSlow::onDisable()
{
}

void NoSlow::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;


	if (this->getMode() == 0) {
		p->set_speed(0.15);
		SDK::Minecraft->timer->SetTimerSpeed(0.95);
	}
	else if (this->getMode() == 1) {
		p->set_speed(0.15);
		//t->SetTimerSpeed(0.95);
	}


}

void NoSlow::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("NoSlow", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle NoSlow", this);

		ImGui::Text("NoSlow Mode");
		ImGui::Combo("NoSlow Mode", &this->getMode(), this->modes, 2);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
