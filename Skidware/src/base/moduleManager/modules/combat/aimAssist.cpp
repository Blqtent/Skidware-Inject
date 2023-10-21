#include "aimAssist.h"
#include "../../commonData.h"
#include "../../../sdk/sdk.h"
#include "../../../util/logger.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../util/math/worldToScreen.h"
#include "../../../util/math/math.h"
#include "../../../menu/menu.h"
#include "../../../java/java.h"

#include <chrono>
#include <random>
#include "antibot.h"
#include "teams.h"

AimAssist::AimAssist() : AbstractModule("AimAssist", Category::COMBAT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

AimAssist* AimAssist::getInstance() {
	static auto* inst = new AimAssist();
	return inst;
}

void AimAssist::onDisable() {
}

void AimAssist::onEnable() {
}


/* 
How this Aim Assist works :

Essentially its a basic aim assist with smoothing, except that there are 2 aim angles caluclated, one at the feet and one at the head.
The reason why this is done is because if you notice while using fusions aim assist, you're free to move your pitch up and down when targetting a player,
however it does not allow you to exceed the players head or feet, meaning you would always be aiming at the player, however freely be able to look at any part of the players body.

Although this can bypass some servers, it does not bypass all of them.
This is because some anticheats don't really give a damn where you are aiming, they mostly want to see how you rotate when you move, and that is where they catch you.

I (deadshell) can create a bypass for it in the future.

For now, if you want to use fusion, just use it with weak settings.

Suggested settings:
30-40 FOV
15-30 Smooth
3.5 - 4 Locking Distance
*/
void AimAssist::onUpdate(const EventUpdate e)
{
	if (!getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (Menu::Open) return;

	if ((aimKey && (!GetAsyncKeyState(VK_LBUTTON) && 1))) {
		AimAssist::data = Vector3();
		return;
	}

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	Vector3 pos = thePlayer->GetPos();
	Vector3 headPos = thePlayer->GetEyePos();
	Vector2 currentLookAngles = thePlayer->GetAngles();

	List playerList = CommonData::getInstance()->playerEntities;


	CEntityPlayer target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = aimDistance;

	// The code from here and below is kind of dog water, however it does the job.
	// The real math for the aim angles if you're interested is located in Math::getAngles()
	// fusion/src/base/util/math/Math.cpp
	auto randomFloat = [](float min, float max)
	{
		float f = (float)rand() / RAND_MAX;
		return min + f * (max - min);
	};


	for (CEntityPlayer player : playerList.toVector<CEntityPlayer>())
	{
		if (!player.isValid() || player.isNULL()) continue;

		if (!player.isValid()
			|| player.isNULL()
			|| player.GetName().starts_with("�r�8[npc]")
			|| !player.isDead() && player.isInvisible() && player.GetName().length() >= 2
			|| player.GetName().contains("]")
			|| player.GetName().contains("[")
			|| player.GetName().contains("-")
			|| player.GetName().contains(":")
			|| player.GetName().contains("+")
			|| player.GetName().contains("cit")
			|| player.GetName().contains("npc")
			)
			continue;
		
		if (Teams::getInstance()->getToggle() && Teams::getInstance()->isTeam(player)) {
			continue;
		}

		if (player.GetName().length() < 0) return;
		if (!Java::Env->IsSameObject(thePlayer->getInstance(), player.getInstance())) {
			if (!thePlayer->CanEntityBeSeen(player.getInstance())) continue;

			float playerHeight = target.GetHeight() - 0.1;


			Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos() + Vector3(0, playerHeight, 0)).Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos()).Invert());
			if (differenceFoot.x < 0) differenceFoot.x = -differenceFoot.x;
			if (differenceFoot.y < 0) differenceFoot.y = -differenceFoot.y;

			float angleYaw = currentLookAngles.x - difference.x;

			Vector3 diff = thePlayer->GetPos() - player.GetPos();
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


	Vector3 ePos = target.GetPos();
	Vector3 eLastPos = target.GetLastTickPos();

	float eHeight = target.GetHeight() - 0.1;
	Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
	Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


	Vector2 anglesFoot = Math::getAngles(headPos, ePos);
	Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

	Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
	Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

	float offset = randomFloat(-AimAssist::randomYaw, AimAssist::randomYaw);
	if (AimAssist::adaptive) {
		if ((GetAsyncKeyState('D') & 0x8000) && !(GetAsyncKeyState('A') & 0x8000)) {
			offset -= AimAssist::adaptiveOffset;
		}

		if ((GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000)) {
			offset += AimAssist::adaptiveOffset;
		}
	}

	float targetYaw = currentLookAngles.x + ((difference.x + offset) / smooth);

	Vector3 renderPos = CommonData::getInstance()->renderPos;
	float renderPartialTicks = CommonData::getInstance()->renderPartialTicks;

	if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y) {
		float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / smooth);
		float targetPitchHead = currentLookAngles.y + (difference.y / smooth);

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
		pitchInfluenced = true;
		targetPitch += randomFloat(-AimAssist::randomPitch, AimAssist::randomPitch);
		thePlayer->SetAngles(Vector2(targetYaw, targetPitch));
	}
	else {
		data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
		pitchInfluenced = false;
		thePlayer->SetAngles(Vector2(targetYaw, currentLookAngles.y + randomFloat(-AimAssist::randomPitch, AimAssist::randomPitch)));
	}

}

void AimAssist::RenderUpdate()
{
	if (!this->getToggle() || !CommonData::getInstance()->dataUpdated) return;
	if (fovCircle) {

		ImVec2 screenSize = ImGui::GetWindowSize();
		float radAimbotFov = (float)(this->fov * PI / 180);
		float radViewFov = (float)(CommonData::getInstance()->fov * PI / 180);
		float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * screenSize.x / 1.7325;

		ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), circleRadius, ImColor(25, 255, 255, 75), circleRadius / 3, 1);
	}

	if (aimAssistFeedback) {
		if (data.x == NAN) return;
		ImVec2 screenSize = ImGui::GetWindowSize();

		Vector2 w2s;
		if (CWorldToScreen::WorldToScreen(data, CommonData::getInstance()->modelView, CommonData::getInstance()->projection, screenSize.x, screenSize.y, w2s))
		{
			if (w2s.x == NAN) return;

			if (pitchInfluenced)
			{
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, w2s.y), ImColor(25, 255, 255), 1.5);
			}
			else {
				ImGui::GetWindowDrawList()->AddLine(ImVec2(screenSize.x / 2, screenSize.y / 2), ImVec2(w2s.x, screenSize.y / 2), ImColor(25, 255, 255), 1.5);
			}
		}
	}

}

void AimAssist::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("", ImVec2(450, 381))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(234402345634000, "Toggle Aim Assist", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		ImGui::SliderFloat("FOV", &this->fov, 5.0f, 180.0f);
		ImGui::SliderFloat("Lock Distance", &this->aimDistance, 1.0f, 8.0f);
		ImGui::SliderFloat("Smoothness", &this->smooth, 1.0f, 90.0f);
		Menu::DoToggleButtonStuff(22645342, "Visbility Check", &this->visibilityCheck);
		Menu::DoToggleButtonStuff(206573465433442, "Left Button To Aim", &this->aimKey);

		ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));
		ImGui::Text("Target Priority");
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 175);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0.55, 0.55, 1));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.65, 0.65, 1));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0.8, 0.8, 1));

		ImGui::Combo("tp", &this->targetPriority, this->targetPriorityList, 3);

		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar();

		ImGui::Separator();

		Menu::DoToggleButtonStuff(5635678756247, "Adapt to strafing", &this->adaptive);
		ImGui::SliderFloat("Adaptive strafing offset", &this->adaptiveOffset, 0.1f, 15.f);
		ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

		ImGui::Separator();
		ImGui::SliderFloat("Yaw Randomness", &this->randomYaw, 0.0f, 10.0f);
		ImGui::SliderFloat("Pitch Randomness", &this->randomPitch, 0.0f, 1);
		ImGui::SetCursorPos(ImVec2(20, ImGui::GetCursorPosY() + 5));

		ImGui::Separator();
		Menu::DoToggleButtonStuff(76523436400, "FOV Circle", &this->fovCircle);
		Menu::DoToggleButtonStuff(230476545677654654, "Feedback Line", &this->aimAssistFeedback);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
