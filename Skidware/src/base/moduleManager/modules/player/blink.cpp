#include "blink.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"
#include <chrono>
#include "../combat/antibot.h"
#include "../combat/teams.h"
#include "../../../util/math/math.h"
Blink::Blink() : AbstractModule("Fakelag", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Blink* Blink::getInstance() {
	static auto* inst = new Blink();
	return inst;
}

void Blink::onDisable() {
}

void Blink::onEnable() {
	timer = 0;
}


void Blink::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	Blink::getInstance()->timer++;

	List playerList = CommonData::getInstance()->playerEntities;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;


	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	Vector3 pos = thePlayer->GetPos();
	Vector3 headPos = thePlayer->GetEyePos();
	Vector2 currentLookAngles = thePlayer->GetAngles();

	for (CEntityPlayer player : playerList.toVector<CEntityPlayer>())
	{
		if (!player.isValid() || player.isNULL()) continue;

		if (Antibot::getInstance()->getToggle() && Antibot::getInstance()->isBot(player)) {
			continue;
		}

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

			if ((abs(difference.x) <= 360) && dist <= 5)
			{
				float health = player.GetHealth();
				switch (3)
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

}

void Blink::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("Blink", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(6890, "Toggle Fakelag", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		//Menu::DoToggleButtonStuff(566578, "Fakelag Throttle", &Blink::throttle);
		if (this->getMode() == 2 || this->getMode() == 3) {
			ImGui::SliderFloat("Throttle Delay", &this->Milliseonds, 1, 150);
			ImGui::SliderFloat("Chance", &this->Chance, 1, 10);
		}
		ImGui::Combo("Mode", &this->getMode(), this->modes, 4);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void Blink::OnReceiveData()
{

	if (!this->getToggle())
		return;

	while (IsKeyBeingDown(this->getKey()) && (GetTickCount64() - timer < Milliseonds * 1000)) {
		Sleep(1);
	}
}
