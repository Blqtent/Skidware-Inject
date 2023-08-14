#include "Strafe.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../player/fastplace.h"
#include "../../../menu/menu.h"
#include "../../../java/java.h"
#include <windows.h>
#include <numbers>
#include "../../../extension/scripting.hpp"

#define M_PI 3.1415926
static uint64_t timer = GetTickCount64();
static double playerSpeed = 0.0;
static bool slowDown{ false };
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
	if (SDK::Minecraft->thePlayer->getMoveStrafe() != 0 && SDK::Minecraft->thePlayer->getMoveForward() != 0) {
		double yaw = get_direction();
		SDK::Minecraft->thePlayer->set_motion_x(-sin(yaw) * speed);
		SDK::Minecraft->thePlayer->set_motion_z(cos(yaw) * speed);
		float y = SDK::Minecraft->thePlayer->getMotion().y;
		SDK::Minecraft->thePlayer->setMotion(Vector3((-sin(yaw) * speed), y, (cos(yaw) * speed)));
	}
}

void Strafe::Update()
{
	if (!Enabled) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	//if (!SDK::Minecraft->thePlayer->isOnGround()) return;
	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;
	CTimer* t = SDK::Minecraft->timer;
	JNIEnv* env = Java::Env;

	auto forward = [&p, &t, &env](float speed)
	{
		float forward = p->getMoveForward();
		float side = p->getMoveStrafe();
		float yaw = p->GetPrevRotationYaw() + (p->GetRotationYaw() - p->GetPrevRotationYaw()) * t->GetRenderPartialTicks();
		if (forward != 0.0f)
		{
			if (side > 0.0f) {
				yaw += ((forward > 0.0f) ? -45 : 45);
			}
			else if (side < 0.0f) {
				yaw += ((forward > 0.0f) ? 45 : -45);
			}
			side = 0.0f;
			if (forward > 0.0f) {
				forward = 1.0f;
			}
			else if (forward < 0.0f) {
				forward = -1.0f;
			}
			float sin = sinf(((yaw + 90.f) * std::numbers::pi / 180.f));
			float cos = cosf(((yaw + 90.f) * std::numbers::pi / 180.f));
			double posX = (double)(forward * speed * cos + side * speed * sin);
			double posZ = (double)(forward * speed * sin - side * speed * cos);
			return Vector3(posX, 0, posZ);
		}
	};
	if (mode == 0) {
		if (p->isOnGround() && (p->getMoveForward() != 0 || p->getMoveStrafe() != 0) && GetTickCount64() - timer > 300) {
			timer = GetTickCount64();
			p->jump();
			playerSpeed = ((Strafe::speed / 1.45) * 0.2873) * 1.90;
			slowDown = true;
		}
		else {
			if (playerSpeed != 0.0) {
				if (slowDown) {
					playerSpeed -= 0.7 * (playerSpeed = 0.2873);
					slowDown = false;
				}
				else {
					playerSpeed -= playerSpeed / 159.0;
				}
			}
		}

		playerSpeed = (((playerSpeed) > ((Strafe::speed / 1.45) * 0.2873)) ? (playerSpeed) : ((Strafe::speed / 1.45) * 0.2873));

		Vector3 dir = forward((float)playerSpeed);
		if (abs(dir.x) < 10.0 && abs(dir.z) < 10.0) { // lil check just incase
			p->setMotion(Vector3(dir.x, p->getMotion().y, dir.z));
		}
	}
	else if (mode == 1) {
		if (p->isOnGround() && (p->getMoveForward() != 0 || p->getMoveStrafe() != 0) && GetTickCount64() - timer > 300) {
			timer = GetTickCount64();
			p->jump();
		}
	}
}

void Strafe::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Strafe", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(23432423, "Toggle Strafe", &Strafe::Enabled);

		Menu::DoSliderStuff(1734563, "Speed", &Strafe::speed, 0, 10);
		ImGui::Text("BHop Mode");
		ImGui::Combo("Mode", &Strafe::mode, Strafe::modes, 2);

		/*if (ImGui::Button("Load Script"))
		{
			scripting::loadScript = true;
		}*/

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
