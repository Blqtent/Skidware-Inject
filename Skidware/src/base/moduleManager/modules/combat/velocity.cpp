#include "velocity.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"
#include "../../../util/math/math.h"
Velocity::Velocity() : AbstractModule("Velocity", Category::COMBAT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Velocity* Velocity::getInstance() {
	static auto* inst = new Velocity();
	return inst;
}

void Velocity::onDisable() {
}

void Velocity::onEnable() {
}



int counter;
void Velocity::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	Vector3 pos = thePlayer->GetPos();
	Vector2 rot = Vector2(thePlayer->GetRotationYaw(), thePlayer->GetRotationPitch());
	float clamped_yaw = Math::wrapAngleTo180(rot.x);
	float yawToAdd = 0;
	for (CEntityPlayer& p : CommonData::getInstance()->playerEntities.toVector<CEntityPlayer>()) {

		if (!p.isValid() || p.isNULL()) continue;

		if (Java::Env->IsSameObject(p.getInstance(), thePlayer->getInstance())) {
			continue;
		}

		Vector3 targetPos = p.GetPos();

		if (onlyTargeting && (targetPos - pos).Dist() >= 5.0f) {
			continue;
		}
		Vector2 target_required_rotation = Math::getAngles(pos, targetPos);

		yawToAdd = target_required_rotation.x - clamped_yaw;

		yawToAdd = Math::wrapAngleTo180(yawToAdd);
		if (!onlyTargeting || std::abs(yawToAdd) < 60) {
			if (this->getMode() == 0) {
				if (thePlayer->getHurtTime() > 3) {
					Vector3 motion = thePlayer->getMotion();
					motion.x = motion.x * (Velocity::Horizontal * 0.01);
					motion.y = motion.y * (Velocity::Vertical * 0.01);
					motion.z = motion.z * (Velocity::Horizontal * 0.01);


					thePlayer->setMotion(motion);
				}
			}
			else if (this->getMode() == 1) {
				if (thePlayer->getHurtTime() > 5 /* && counter++ % 2 == 0 */) {
					thePlayer->setKeyJump(true); 
				}
				else if (!GetAsyncKeyState(VK_SPACE) & 1){
					thePlayer->setKeyJump(false);
				}
			}
			else if (this->getMode() == 2) {
				if (thePlayer->getHurtTime() > 5) {
					thePlayer->setOnGround(true);
				}
			}
			else if (this->getMode() == 3) {
				if (thePlayer->getHurtTime() > 6) {
					thePlayer->set_speed(0.025);
				}
			}
			else if (this->getMode() == 4) {
				if (thePlayer->getHurtTime() == 9) {
					thePlayer->setMotion(Vector3(thePlayer->getMotion().x * 0.0, thePlayer->getMotion().y, thePlayer->getMotion().z * 0.0));
				}
				if (thePlayer->getHurtTime() == 8) {
					thePlayer->setMotion(Vector3(thePlayer->getMotion().x * 0.4, thePlayer->getMotion().y, thePlayer->getMotion().z * 0.4));
				}
				if (thePlayer->getHurtTime() == 7) {
					thePlayer->setMotion(Vector3(thePlayer->getMotion().x * 0.5, thePlayer->getMotion().y, thePlayer->getMotion().z * 0.5));
				}
				if (thePlayer->getHurtTime() == 6) {
					thePlayer->setMotion(Vector3(thePlayer->getMotion().x * 0.8, thePlayer->getMotion().y, thePlayer->getMotion().z * 0.8));
				}
			}
			else if (this->getMode() == 5) {
				if (thePlayer->getHurtTime() > 8) {
					thePlayer->setPos(thePlayer->GetPos().x, thePlayer->GetPos().y - 0.26, thePlayer->GetPos().z);
					thePlayer->setPos(thePlayer->GetPos().x, thePlayer->GetPos().y + 0.3, thePlayer->GetPos().z);					//thePlayer->set_speed(10);
				}//thePlayer->set_speed(10);
			}
		}
	}
	

}

void Velocity::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("velocity", ImVec2(450, 250))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2134078, "Toggle Velocity", this);
		Menu::DoToggleButtonStuff(3456411312, "Only While Targeting", &this->onlyTargeting);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		if (this->getMode() == 0) {
			ImGui::SliderFloat("Horizontal", &this->Horizontal, 0, 100, "%.0f");
			ImGui::SliderFloat("Vertical", &this->Vertical, 0, 100, "%.0f");
		}
		ImGui::Combo("Mode", &this->getMode(), this->modes, 6);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
