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

	float dist = 1000000000.0f;

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

			float dist2 = Math::distance(thePlayer->GetPos().x, player.GetPos().x, thePlayer->GetPos().y, player.GetPos().y, thePlayer->GetPos().z, player.GetPos().z);

			if (dist2 < this->dist) {
				this->target = player;
				this->dist = dist2;
			}

		}
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
			ImGui::SliderFloat("Throttle Delay", &this->Milliseonds, 1, 1000);
			//ImGui::SliderFloat("Chance", &this->Chance, 1, 10);
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
