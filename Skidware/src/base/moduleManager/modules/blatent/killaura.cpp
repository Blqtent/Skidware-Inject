#pragma once
#include "killaura.h"
#include <mutex>
#include <random>
#include <cstring>
#include <iostream>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../util/math/math.h"
#include "../combat/antibot.h"
#include "../combat/teams.h"
long lastClickTime = 0;
int nextCps = 10;
long counter = 0;
double distance(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return distance(y1 - y2, distance(x1 - x2, z1 - z2));
}

bool isMove() {
	if (!CommonData::getInstance()->SanityCheck()) return NULL;

	CEntityPlayerSP* p = SDK::Minecraft->thePlayer;

	return (p->getMoveForward() != 0 || p->getMoveStrafe() != 0);
}

Killaura::Killaura() : AbstractModule("Killaura", Category::BLATENT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Killaura* Killaura::getInstance() {
	static auto* inst = new Killaura();
	return inst;
}

void Killaura::onDisable() {
	SDK::Minecraft->timer->SetTimerSpeed(1);
	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
	SendMessage(Menu::HandleWindow, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
}

void Killaura::onEnable() {
	
}

void Killaura::onUpdate(const EventUpdate e) {
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	List playerList = CommonData::getInstance()->playerEntities;
	CEntityPlayerSP thePlayer = *SDK::Minecraft->thePlayer;

	Vector3 headPos = thePlayer.GetEyePos();
	Vector2 currentLookAngles = thePlayer.GetAngles();

	CEntityPlayer target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = range;

	// The code from here and below is kind of dog water, however it does the job.
	// The real math for the aim angles if you're interested is located in Math::getAngles()
	// fusion/src/base/util/math/Math.cpp
	auto list = playerList.toVector<CEntityPlayer>();
	for (CEntityPlayer player : list)
	{

		if (!player.isValid() || player.isNULL()) continue;

		if (Antibot::getInstance()->getToggle() && Antibot::getInstance()->isBot(player)  ) {
			continue;
		}
		
		if (Teams::getInstance()->getToggle() && Teams::getInstance()->isTeam(player)  ) {
			continue;
		}

		if (player.GetName().length() < 0) return;
		if (!Java::Env->IsSameObject(thePlayer.getInstance(), player.getInstance())) {
			if (!thePlayer.CanEntityBeSeen(player.getInstance())) continue;

			float playerHeight = target.GetHeight() - 0.1;

			Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos() + Vector3(0, playerHeight, 0)).Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos()).Invert());
			if (differenceFoot.x < 0) differenceFoot.x = -differenceFoot.x;
			if (differenceFoot.y < 0) differenceFoot.y = -differenceFoot.y;

			float angleYaw = currentLookAngles.x - difference.x;

			Vector3 diff = thePlayer.GetPos() - player.GetPos();
			float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));

			if ((abs(difference.x) <= fov) && dist <= realAimDistance)
			{
				float health = player.GetHealth();
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

	if (!target.getInstance()) {
		Vector3 null;
		data = null;
		return;
	}

	if (this->getMode() == 0 || this->getMode() == 2) {
		Vector3 ePos = target.GetPos();
		Vector3 eLastPos = target.GetLastTickPos();

		float eHeight = target.GetHeight() - 0.1;
		Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
		Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


		Vector2 anglesFoot = Math::getAngles(headPos, ePos);
		Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

		Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
		Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

		float offset = 0;

		float targetYaw = currentLookAngles.x + ((difference.x + offset) / 1.0f);

		Vector3 renderPos = CommonData::getInstance()->renderPos;
		float renderPartialTicks = CommonData::getInstance()->renderPartialTicks;

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
			//targetPitch += randomFloat(-this->randomPitch, this->randomPitch);
			if (this->getMode() == 0)
				thePlayer.SetAngles(Vector2(targetYaw, targetPitch));
			else if (this->getMode() == 2) {
				thePlayer.sendGroundPacket(thePlayer.C03PacketPlayer(thePlayer.isOnGround(), targetYaw, targetPitch));
			}
		}
		else {
			data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			//pitchInfluenced = false;
			if (this->getMode() == 0)
				thePlayer.SetAngles(Vector2(targetYaw, currentLookAngles.y + 0));
			else if (this->getMode() == 2) {
				thePlayer.sendGroundPacket(thePlayer.C03PacketPlayer(thePlayer.isOnGround(), targetYaw, currentLookAngles.y + 0));
			}
		}
	}
	if (!target.getInstance()) {
		return;
	}

	if (keepsprint && thePlayer.getMoveForward() != 0) {
		//float dist = (100 - (100 / 100));
		thePlayer.set_speed(thePlayer.get_speed() * 1.0095);
		thePlayer.setSprint(true);
	}

	else if (autoblock == true && (this->getMode() == 1 || this->getMode() == 2)) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		if (isMove()) {
			thePlayer.set_speed(0.21);
			SDK::Minecraft->timer->SetTimerSpeed(0.95);
		}
	}
	counter++;
	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;

	if (this->getMode() == 0) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		CommonData::getInstance()->isCombat = true;
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

	}
	else if (this->getMode() == 1 || this->getMode() == 2) {
		thePlayer.swingItem();
		CommonData::getInstance()->isCombat = true;
		thePlayer.attackEntity(&thePlayer, target.getInstance());
	}

	if (autoblock == true && this->getMode() == 0) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);

		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		if (isMove())
			thePlayer.set_speed(0.155);
	}



	lastClickTime = milli;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(this->leftMinCps, this->leftMaxCps);
	nextCps = distrib(gen);
}
void Killaura::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("Killaura", ImVec2(450, 381))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(45646, "Toggle Killaura", this);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		ImGui::SliderFloat("Min CPS", &this->leftMinCps, 1, 20);
		ImGui::SliderFloat("Max CPS", &this->leftMaxCps, 1, 20);
		ImGui::SliderFloat("FOV", &this->fov, 1, 360);
		/*if (leftMinCps > leftMaxCps) {
			leftMinCps = leftMaxCps;
		}*/
		Menu::DoToggleButtonStuff(2524, "Autoblock", &this->autoblock);
		Menu::DoToggleButtonStuff(679067, "Keepsprint", &this->keepsprint);
		ImGui::SliderFloat("Range", &this->range, 3, 6);
		ImGui::Text("Target Priority");
		ImGui::Combo("Target", &this->targetPriority, Killaura::targetPriorityList, 3);
		ImGui::Text("Mode");
		ImGui::Combo("Rot", &this->getMode(), Killaura::modes, 3);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}