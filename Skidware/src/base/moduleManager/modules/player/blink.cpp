#include "blink.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"

Blink::Blink() : AbstractModule("Fakelag", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Blink* Blink::getInstance() {
	static auto* inst = new Blink();
	return inst;
}

void Blink::onDisable() {
}

void Blink::onEnable() {
}


void Blink::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;


}

void Blink::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Blink", ImVec2(450, 75))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(6890, "Toggle Fakelag", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		//Menu::DoToggleButtonStuff(566578, "Fakelag Throttle", &Blink::throttle);
		//Menu::DoSliderStuff(566578, "Fakelag Delay", &this->Milliseonds, 1, 10000);
		ImGui::Combo("Bind Mode", &this->getMode(), this->modes, 2);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Blink::OnReceiveData()
{

	if (!this->getToggle())
		return;

	while (IsKeyBeingDown(this->getKey()) && (GetTickCount64() - timer < Milliseonds * 1000)) {
		Sleep(1);
	}
}