#pragma once
#include "killaura.h"
#include <mutex>
#include <random>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../util/math/math.h"
#include "../combat/antibot.h"
long lastClickTime = 0;
int nextCps = 10;
double distance(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return distance(y1 - y2, distance(x1 - x2, z1 - z2));
}

bool isMove() {
	if (!CommonData::SanityCheck()) return NULL;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;

	return (p->getMoveForward() != 0 || p->getMoveStrafe() != 0);
}


void Killaura::Update() {
	if (!Enabled) return;
	if (Menu::Open) return;
	if (!CommonData::SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	Vector3 headPos = thePlayer->GetEyePos();
	Vector2 currentLookAngles = thePlayer->GetAngles();

	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	CommonData::PlayerData target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = range;

	// The code from here and below is kind of dog water, however it does the job.
	// The real math for the aim angles if you're interested is located in Math::getAngles()
	// fusion/src/base/util/math/Math.cpp

	for (CommonData::PlayerData player : playerList)
	{
		if (Antibot::isBot(player) && Antibot::Enabled) {
			continue;
		}
		if (player.name.length() < 0) return;
		if (!Java::Env->IsSameObject(thePlayer->GetInstance(), player.obj.GetInstance())) {
			if (!thePlayer->CanEntityBeSeen(player.obj.GetInstance())) continue;
			
			float playerHeight = target.height - 0.1;


			Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.pos + Vector3(0, playerHeight, 0)).Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.pos).Invert());
			if (differenceFoot.x < 0) differenceFoot.x = -differenceFoot.x;
			if (differenceFoot.y < 0) differenceFoot.y = -differenceFoot.y;

			float angleYaw = currentLookAngles.x - difference.x;

			Vector3 diff = thePlayer->GetPos() - player.pos;
			float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));

			if ((abs(difference.x) <= fov) && dist <= realAimDistance)
			{
				float health = player.health;
				switch (targetPriority)
				{
				case 1:
					if (finalHealth > health)
					{
						target = player;
						finalHealth = health;
					}
					break;

				case 2:
					if (finalDiff > difference.x)
					{
						target = player;
						finalDiff = difference.x;
					}
					break;
				default:
					if (finalDist > dist)
					{
						target = player;
						finalDist = (float)dist;
					}
				}
			}
		}
	}

	if (!target.obj.GetInstance()) {
		Vector3 null;
		data = null;
		return;
	}

	if (mode == 0) {
		Vector3 ePos = target.pos;
		Vector3 eLastPos = target.lastPos;

		float eHeight = target.height - 0.1;
		Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
		Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


		Vector2 anglesFoot = Math::getAngles(headPos, ePos);
		Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

		Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
		Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

		float offset = 0;

		float targetYaw = currentLookAngles.x + ((difference.x + offset) / 1.0f);

		Vector3 renderPos = CommonData::renderPos;
		float renderPartialTicks = CommonData::renderPartialTicks;

		if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y) {
			float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / 1.0f);
			float targetPitchHead = currentLookAngles.y + (difference.y / 1.0f);

			float diffFoot = currentLookAngles.y - targetPitchFoot;
			float diffHead = currentLookAngles.y - targetPitchHead;
			diffFoot = diffFoot < 0 ? -diffFoot : diffFoot;
			diffHead = diffHead < 0 ? -diffHead : diffHead;

			float targetPitch;
			if (diffFoot > diffHead)
			{
				targetPitch = targetPitchHead;
				data = renderPos - Vector3(0, 0.21, 0) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
			}
			else
			{
				targetPitch = targetPitchFoot;
				data = renderPos - Vector3(0, 0.23, 0) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			}
			//pitchInfluenced = true;
			//targetPitch += randomFloat(-Killaura::randomPitch, Killaura::randomPitch);
			thePlayer->SetAngles(Vector2(targetYaw, targetPitch));
		}
		else {
			data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			//pitchInfluenced = false;
			thePlayer->SetAngles(Vector2(targetYaw, currentLookAngles.y + 0));
		}
	}
	if (!target.obj.GetInstance()) {
		return;
	}

	if (keepsprint && thePlayer->getMoveForward() != 0) {
		thePlayer->setSprint(true);
	}

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;
	if (mode == 0) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
	}
	else if (mode == 1) {
		thePlayer->swingItem();
		thePlayer->attackEntity(thePlayer, target.obj.GetInstance());
	}
	if (autoblock == true && mode == 0) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);

		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		if (isMove())
			thePlayer->set_speed(0.155);
	}
	else if (autoblock == true && mode == 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);

		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));

	}
	

	lastClickTime = milli;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(Killaura::leftMinCps, Killaura::leftMaxCps);
	nextCps = distrib(gen);
}

void Killaura::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("Killaura", ImVec2(450, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(45646, "Toggle Killaura", &Killaura::Enabled);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(13141, "Min CPS", &Killaura::leftMinCps, 1, 20);
		Menu::DoSliderStuff(242, "Max CPS", &Killaura::leftMaxCps, 1, 20);
		Menu::DoSliderStuff(1324124, "FOV", &Killaura::fov, 1, 360);
		if (leftMinCps > leftMaxCps) {
			leftMinCps = leftMaxCps;
		}
		Menu::DoToggleButtonStuff(2524, "Autoblock", &Killaura::autoblock);
		Menu::DoToggleButtonStuff(679067, "Keepsprint", &Killaura::keepsprint);
		Menu::DoSliderStuff(34508, "Range", &Killaura::range, 3, 6);
		ImGui::Text("Target Priority");
		ImGui::Combo("Target", &Killaura::targetPriority, Killaura::targetPriorityList, 3);
		ImGui::Text("Mode");
		ImGui::Combo("Rot", &Killaura::mode, Killaura::modes, 2);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}

