#include "tower.h"
#include "../../../menu/menu.h"
#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;
int count = 0;
/*
float getStrafeMultiplier() {
	float multiplier = 0.0f;
	CMinecraft* mc = SDK::Minecraft;
	CommonData::Direction dir = CommonData::NONE;
	if (mc->thePlayer->getMoveStrafe() > 0) {
		multiplier += 270.0f;
		dir = CommonData::RIGHT;
	}
	else if (mc->thePlayer->getMoveStrafe() < 0) {
		multiplier += 90.0f;
		dir = CommonData::LEFT;
	}
	else if (mc->thePlayer->getMoveForward() < 0) {
		multiplier += 180.0f;
		dir = CommonData::BACKWARDS;
	}

	if (dir == CommonData::LEFT && mc->thePlayer->isMovingBackwards()) multiplier += 45.0f;
	else if (dir == CommonData::RIGHT && mc->thePlayer->isMovingBackwards()) multiplier -= 45.0f;
	else if (dir == CommonData::LEFT && mc->thePlayer->isMovingForwards()) multiplier -= 45.0f;
	else if (dir == CommonData::RIGHT && mc->thePlayer->isMovingForwards()) multiplier += 45.0f;

	return multiplier;
}
*/
Tower::Tower() : AbstractModule("Scaffold", Category::BLATENT, 'Y') {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Tower* Tower::getInstance()
{
	static auto* inst = new Tower();
	return inst;
}

void Tower::onEnable()
{
	if (CommonData::getInstance()->SanityCheck())
	{
		orYaw = SDK::Minecraft->thePlayer->GetRotationYaw();
		orPitch = SDK::Minecraft->thePlayer->GetRotationPitch();
		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw() + 180, SDK::Minecraft->thePlayer->isOnGround() ? 80 : 73));
		count = 0;
	}
}

void Tower::onDisable()
{

	if (!CommonData::getInstance()->SanityCheck())
		return;
	SDK::Minecraft->thePlayer->setSneak(false);
	SDK::Minecraft->thePlayer->SetAngles(Vector2(orYaw, orPitch));

}

void Tower::onUpdate(const EventUpdate e)
{
	
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	jclass blockClass;
	Java::AssignClass("net.minecraft.item.ItemBlock", blockClass);

	//CMinecraft* mc = SDK::Minecraft;
	count++;
	if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
		SDK::Minecraft->thePlayer->setSneak(true);
		//SDK::Minecraft->thePlayer->setMotion(Vector3(0, 100000000000, 0));
	}
	else {
		SDK::Minecraft->thePlayer->setSneak(false);
	}

	if (tower && !SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1.5, SDK::Minecraft->thePlayer->GetPos().z) && GetAsyncKeyState(VK_SPACE) & 0x8000) {

		SDK::Minecraft->thePlayer->setMotion(Vector3(0, count % 2 == 0 ? 0.1 : 0.32, 0));
		SDK::Minecraft->thePlayer->setOnGround(true);

		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw(), 90));
	}
	else {
		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw(), SDK::Minecraft->thePlayer->isOnGround() ? 80 : 75));
	}

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
	SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
	SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

	rightLastClickTime = milli;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(8, 14);
	rightNextCps = distrib(gen);

}

void Tower::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Scaffold", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(3465, "Toggle Scaffold", this);
		Menu::DoToggleButtonStuff(3465, "Tower", &this->tower);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
