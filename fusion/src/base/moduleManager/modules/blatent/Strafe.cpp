#include "Strafe.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../player/fastplace.h"
#include "../../../menu/menu.h"
#define M_PI 3.1415926

double toRadians(float degrees) {
	return degrees * (M_PI / 180);
}

float get_direction()
{
	float yaw = SDK::Minecraft->thePlayer->GetRotationYaw();
	float strafe = 45;
	// add 180 to the yaw to strafe backwards
	if (SDK::Minecraft->thePlayer->getMoveForward() < 0) {
		// invert our strafe to -45
		strafe = -45;
		yaw += 180;
	}
	if (SDK::Minecraft->thePlayer->getMoveStrafe() > 0) {
		// subtract 45 to strafe left forward
		yaw -= strafe;
		// subtract an additional 45 if we do not press W in order to get to -90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw -= 45;
		}
	}
	else if (SDK::Minecraft->thePlayer->getMoveStrafe() < 0) {
		// add 45 to strafe right forward
		yaw += strafe;
		// add 45 if we do not press W in order to get to 90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw += 45;
		}
	}
	return yaw;
}

float get_speed()
{
	Vector3 velocity_vector = SDK::Minecraft->thePlayer->getMotion();

	return sqrt(SDK::Minecraft->thePlayer->get_motion_x() * SDK::Minecraft->thePlayer->get_motion_x() + SDK::Minecraft->thePlayer->get_motion_z() * SDK::Minecraft->thePlayer->get_motion_z());
}

bool isStrafing() {
	return SDK::Minecraft->thePlayer->getMoveStrafe() != 0;
}

bool isMovingForwardsOrBackwards() {
	return SDK::Minecraft->thePlayer->getMoveForward() != 0;
}

void set_speed(const float speed)
{
	
	if (isStrafing() || isMovingForwardsOrBackwards()) {
		double yaw = get_direction();
		SDK::Minecraft->thePlayer->set_motion_x(-sin(yaw) * speed);
		SDK::Minecraft->thePlayer->set_motion_z(cos(yaw) * speed);
	}
	

}




void Strafe::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;
	if (!SDK::Minecraft->thePlayer->isOnGround()) return;
	set_speed(get_speed());
}

void Strafe::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Strafe", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Strafe", &Strafe::Enabled);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
