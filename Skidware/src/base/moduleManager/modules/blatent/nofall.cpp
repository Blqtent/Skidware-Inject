#include "nofall.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

static uint64_t timer = GetTickCount64();

Nofall::Nofall() : AbstractModule("Nofall", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}


Nofall* Nofall::getInstance() {
	static auto* inst = new Nofall();
	return inst;
}

void Nofall::onDisable() {
}

void Nofall::onEnable() {
}


void Nofall::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	CTimer* t = SDK::Minecraft->timer;
	JNIEnv* env = Java::Env;
	if (this->getMode() == 0) {
		if (p->fallDistance() > 2.5 && !(p->getHurtTime() > 0)) {
			p->setMotion(Vector3(p->getMotion().x, -11, p->getMotion().z));
		}
	}
	else if (this->getMode() == 1) {
		if (p->isOnGround() && !(p->getHurtTime() > 0)) {
			p->setMotion(Vector3(p->getMotion().x, -11, p->getMotion().z));
		}
	}

}

void Nofall::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Nofall", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Nofall", this);

		ImGui::Text("Nofall Mode");
		ImGui::Combo("Nofall Mode", &this->getMode(), this->modes, 2);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}