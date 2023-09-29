#include "antivoid.h"
#include "../../../menu/menu.h"


Antivoid::Antivoid() : AbstractModule("Antivoid", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Antivoid* Antivoid::getInstance() {
	static Antivoid* inst = new Antivoid();
	//Logger::Log("Antivoid");
	return inst;
}

void Antivoid::onDisable() {
}

void Antivoid::onEnable() {
}

void Antivoid::onUpdate(EventUpdate e)
{
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	if (!this->getToggle()) {
		return;
	}

	/* 1-2 Flags BMC */
	if (getMode() == 0) {
		if (p->fallDistance() > 6) {
			p->setMotion(Vector3(p->getMotion().x, -0.68, p->getMotion().z));
		}

		/* We can vanilla nofall with the same amount of flags. */
		if (p->fallDistance() > 2.5 && !(p->getHurtTime() > 0)) {
			p->setMotion(Vector3(p->getMotion().x, -11, p->getMotion().z));
		}
	}

	/* Flagless BMC */
	if (getMode() == 1) {
		if (p->fallDistance() > 6) {
			p->setMotion(Vector3(p->getMotion().x, 1, p->getMotion().z));
			p->setFallDistance(0);
		}
	}
	/* NCP */
	if (getMode() == 2) {
		if (p->fallDistance() > 6) {
			p->setMotion(Vector3(p->getMotion().x, -0.01, p->getMotion().z));
			p->setFallDistance(0);
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
		ImGui::Combo("Antivoid Mode", &this->getMode(), this->modes, 3);


		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
