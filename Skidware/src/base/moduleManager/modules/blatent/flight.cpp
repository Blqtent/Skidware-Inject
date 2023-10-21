#include "flight.h"
#include "../../../menu/menu.h"


//void Flight::Update()
//{
//	if (Menu::Open) return;
//	if (!CommonData::getInstance()->SanityCheck()) return;
//	if (!Enabled) {
//		return;
//	}
//
//	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
//	if (mode == 0) {
//		p->setMotion(Vector3(100000000000, 0, 100000000000));
//	}
//	else if (mode == 1) {
//		p->setOnGround(true);
//	}
//
//}
//
//void Flight::RenderMenu()
//{
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
//
//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
//	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
//
//	if (ImGui::BeginChild("Flight", ImVec2(450, 100))) {
//
//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
//		Menu::DoToggleButtonStuff(235354, "Toggle Flight", &Flight::Enabled);
//		if (mode == 11000)
//			Menu::DoSliderStuff(9864, "Glide Speed", &Flight::glideSpeed, -1, 1);
//		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);
//
//		ImGui::Text("Flight Mode");
//		ImGui::Combo("Flight Mode", &Flight::mode, Flight::modes, 2);
//
//		ImGui::EndChild();
//	}
//	ImGui::PopStyleVar();
//	ImGui::PopStyleColor();
//}
//Flight::Flight() : AbstractModule("Sprint", Category::MOVEMENT, 'R') {
//    EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
//    //EventManager::getInstance().reg(Events::EventUpdate, [this] { onUpdate(); });
//}

Flight::Flight() : AbstractModule("Flight", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Flight* Flight::getInstance() {
    static auto* inst = new Flight();
    return inst;
}



void Flight::onDisable() {
	if (CommonData::getInstance()->SanityCheck())
		SDK::Minecraft->thePlayer->set_speed(0);

}

void Flight::onEnable() {
	if (CommonData::getInstance()->SanityCheck()) {
		CEntityPlayerSP* p = SDK::Minecraft->thePlayer;

		p->sendPacket(p->C04PacketPos(p->GetPos().x, p->GetPos().y + 3.001, p->GetPos().z, false));
		p->sendPacket(p->C04PacketPos(p->GetPos().x, p->GetPos().y, p->GetPos().z, false));
		p->sendPacket(p->C04PacketPos(p->GetPos().x, p->GetPos().y, p->GetPos().z, true));
	}
	count = 0;
}

void Flight::onUpdate(const EventUpdate e) {
    if (!this->getToggle())return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	count++;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	if (this->getMode() == 0) {
		p->set_speed(glideSpeed);

		p->setMotion(Vector3(p->getMotion().x, 0, p->getMotion().z));
	}
	else if (this->getMode() == 1) {
		if (p->getMotion().y < 0)
			p->setOnGround(true);
	}
	else if (this->getMode() == 2) {
		p->set_speed(glideSpeed);

		p->setMotion(Vector3(p->getMotion().x, 0, p->getMotion().z));

		if (!(p->getMoveForward() != 0 || p->getMoveStrafe() != 0)) {
			p->setMotion(Vector3(0, 0, 0));
		}

		if (GetAsyncKeyState(VK_LSHIFT)) {
			p->setMotion(Vector3(p->getMotion().x, -0.75, p->getMotion().z));
		}
		if (GetAsyncKeyState(VK_SPACE)) {
			p->setMotion(Vector3(p->getMotion().x, 0.75, p->getMotion().z));
		}
	}
	else if (this->getMode() == 3) {
		if (!p->isOnGround() && p->fallDistance() > 0) {
			if (count % 5 == 0) {
				p->setMotion(Vector3(p->getMotion().x, -0.05, p->getMotion().z));
			}
			else {
				p->setMotion(Vector3(p->getMotion().x, -0.3, p->getMotion().z));

			}

			p->set_speed(0.25);
		}
	}

	else if (this->getMode() == 4) {
		/*
		Vector3 pos = p->GetPos();
		Vector2 rot(p->GetRotationYaw(), p->GetRotationPitch());
		const float PI = 3.1415926535;
		float yaw = rot.x * (PI / 180.0f);
		float pitch = rot.y * (PI / 180.0f);
		const float move_forward = 0.05f;
		Vector3 motion{};
		float hypxz = std::cos(pitch) * move_forward;
		motion.z = std::cos(yaw) * hypxz;
		motion.x = -std::sin(yaw) * hypxz;
		motion.y = -std::sin(pitch) * move_forward;
		pos = pos + motion;
		//p->sendPacket(p->C04PacketPos(pos.x, pos.y, pos.z, false));
		p->setPos(pos.x, p->GetPos().y - 0.01, pos.z);
		*/



		if (p->getHurtTime() > 0) {
			this->isHurt = true;
		}
		if (isHurt) {
			p->set_speed(0.35);
			p->setMotion(Vector3(p->getMotion().x, 0, p->getMotion().z));
		}

	}

}

void Flight::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Flight", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

		Menu::DoToggleButtonStuff(235354, "Toggle Flight",this);
		if (getMode() == 0 || getMode() == 2)
			ImGui::SliderFloat("Speed", &this->glideSpeed, 0, 5);
		//Menu::DoToggleButtonStuff(124343343, "Antikick", &Flight::antikick);

		ImGui::Text("Flight Mode");
		ImGui::Combo("Flight Mode", &Flight::getMode(), Flight::modes, 5);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}