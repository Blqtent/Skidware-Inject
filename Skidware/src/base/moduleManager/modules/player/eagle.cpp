#include "eagle.h"
#include "../../commonData.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"


Eagle::Eagle() : AbstractModule("Eagle", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Eagle* Eagle::getInstance() {
	static auto* inst = new Eagle();
	return inst;
}

void Eagle::onDisable() {
	if (!CommonData::getInstance()->SanityCheck())
		return;
	SDK::Minecraft->thePlayer->setSneak(false);

}

void Eagle::onEnable() {
}


void Eagle::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;

	if (!CommonData::getInstance()->SanityCheck()) return;
	if (!safewalk) {
		if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
			SDK::Minecraft->thePlayer->setSneak(true);
		}
		else {
			SDK::Minecraft->thePlayer->setSneak(false);
		}
	}
	else {
		if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
			SDK::Minecraft->thePlayer->setSneak(true);
		}
	}
}

void Eagle::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Eagle", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(245309786, "Toggle Eagle", this);

		ImGui::Checkbox("Safewalk", &this->safewalk);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
