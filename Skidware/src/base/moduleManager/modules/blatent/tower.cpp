#include "tower.h"
#include "../../../menu/menu.h"
Tower::Tower() : AbstractModule("Scaffold", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Tower* Tower::getInstance()
{
	static auto* inst = new Tower();
	return inst;
}

void Tower::onEnable()
{
	SDK::Minecraft->thePlayer->SetAngles(Vector2(-404.581, 76.6119));

}

void Tower::onDisable()
{
	SDK::Minecraft->thePlayer->SetAngles(Vector2(orYaw, orPitch));
}

void Tower::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	CMinecraft* mc = SDK::Minecraft;
	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
/*	if (GetAsyncKeyState('W') & 0x8000) {

	}*/
	if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
		SDK::Minecraft->thePlayer->setSneak(true);
	}
	else {
		SDK::Minecraft->thePlayer->setSneak(false);
	}
	//mc->thePlayer->setMotion(Vector3(0, 0.42, 0));
	SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
	SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

}

void Tower::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Tower", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(3465, "Toggle Scaffold", this);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
