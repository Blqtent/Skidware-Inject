#include "criticals.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../player/blink.h"
static uint64_t timer = GetTickCount64();
bool should = false;
long count = 0;
Criticals::Criticals() : AbstractModule("Criticals", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}


Criticals* Criticals::getInstance() {
	static auto* inst = new Criticals();
	return inst;
}

void Criticals::onDisable() {
	Blink::getInstance()->shouldSpoof = false;
	hits = 0;
}

void Criticals::onEnable() {
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	/* No Ground */
	if (this->getMode() == 0 && p->isOnGround() == true) {
		p->jump();
	}

	hits = 0;
}

void Criticals::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	CTimer* t = SDK::Minecraft->timer;
	JNIEnv* env = Java::Env;

	/* No Ground */
	if (this->getMode() == 0 && p->isOnGround() == true) {
		p->setOnGround(false);
	}
}

void Criticals::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Criticals", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Criticals", this);

		ImGui::Text("Criticals Mode");
		ImGui::Combo("Criticals Mode", &this->getMode(), this->modes, 1);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}