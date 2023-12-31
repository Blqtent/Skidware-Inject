#include "nofall.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../player/blink.h"
static uint64_t timer = GetTickCount64();
bool should = false;
long count = 0;
Nofall::Nofall() : AbstractModule("Nofall", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}


Nofall* Nofall::getInstance() {
	static auto* inst = new Nofall();
	return inst;
}

void Nofall::onDisable() {
	Blink::getInstance()->shouldSpoof = false;
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
	else if (this->getMode() == 2) {
		if (p->fallDistance() > 2.5) {
			p->setMotion(Vector3(p->getMotion().x, 0.1, p->getMotion().z));
			p->setFallDistance(0);
		}
	}
	else if (this->getMode() == 3) {
		if (p->fallDistance() > 2) {
			p->sendPacket(p->C03PacketPlayer(true, p->GetRotationYaw(), p->GetRotationPitch()));
			p->setFallDistance(0);

		}
	}
	else if (this->getMode() == 4) {
		if (p->fallDistance() > 4) {
			p->sendPacket(p->C03PacketPlayer(true, p->GetRotationYaw(), p->GetRotationPitch()));
			//p->C03PacketPlayer(true);
			p->setFallDistance(0);
		}
	}
	else if (this->getMode() == 5) {

		if (p->isOnGround()) {
			count++;
		}
		
		if (p->fallDistance() > 2) {
			p->sendPacket(p->C03PacketPlayer(true, p->GetRotationYaw(), p->GetRotationPitch()));
			p->setFallDistance(0);

		}

		Blink::getInstance()->shouldSpoof = true;

		if (count >= 150) {
			//Blink::getInstance()->shouldSpoof = false;
			count = 0;
			this->toggle();
			
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
		ImGui::Combo("Nofall Mode", &this->getMode(), this->modes, 6);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}