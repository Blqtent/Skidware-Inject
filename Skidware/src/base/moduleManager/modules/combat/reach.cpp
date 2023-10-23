#include "reach.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include "../../../util/logger.h"
#include "../../../java/java.h"
#include "../../../util/math/math.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../player/blink.h"
#include <chrono>
#include "antibot.h"
#include "teams.h"
#include "../../../patcher/patcher.h"
Reach::Reach() : AbstractModule("Reach", Category::COMBAT) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Reach* Reach::getInstance() {
	static auto* inst = new Reach();
	return inst;
}

void Reach::onDisable() {
	if (!CommonData::getInstance()->SanityCheck()) return;

	Patcher::put("reach_distance", "3.0");


	return;
}

void Reach::onEnable() {
	ticks = 0;
}


std::chrono::steady_clock::time_point lastUpdate;
void Reach::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	if (this->getMode() == 0) {
		std::chrono::steady_clock::time_point nanoTime = std::chrono::high_resolution_clock::now();

		// Calculate the elapsed time in nanoseconds
		float elapsed = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(nanoTime - lastUpdate).count() / 1000000;
		if (elapsed < 20)
			return;
		else
			lastUpdate = nanoTime;

		CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
		List playerList = CommonData::getInstance()->playerEntities;

		Vector2 playerAngles = thePlayer->GetAngles();
		Vector3 playerPos = thePlayer->GetPos();

		for (CEntityPlayer target : playerList.toVector<CEntityPlayer>())
		{
			if (!target.isValid() || target.isNULL()) continue;

			float distance = ReachDistance;
			if (Java::Env->IsSameObject(thePlayer->getInstance(), target.getInstance())) continue;

			BoundingBox targetBB = target.GetBB().GetNativeBoundingBox();

			float hypothenuseDistance = (float)sqrt(pow((playerPos - target.GetPos()).x, 2) + pow((playerPos - target.GetPos()).z, 2));

			if (distance > hypothenuseDistance)
				distance -= hypothenuseDistance;

			float difference = Math::wrapAngleTo180(playerAngles.x - Math::getAngles(playerPos, target.GetPos()).x);

			if (std::abs(difference) > 180.0f)
				continue;

			float cos = std::cos(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).x + 90.0f));
			float sin = std::sin(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).x + 90.0f));
			float cosPitch = std::cos(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).y));
			float sinPitch = std::sin(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).y));

			float x = target.GetPos().x - (cos * distance * cosPitch);
			float y = target.GetPos().y + (distance * sinPitch);
			float z = target.GetPos().z - (sin * distance * cosPitch);

			float entityWidth = 0.6f;
			float bbWidth = entityWidth / 2.0f;

			BoundingBox newBB{
				(double)x - bbWidth,
				(double)y,
				//targetBB.minY,
				(double)z - bbWidth,

				(double)x + bbWidth,
				(double)y + 2,
				//targetBB.maxY,
				(double)z + bbWidth
			};

			target.SetBB(newBB);
		}
	}
	else if (this->getMode() == 1) {
		CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
		List playerList = CommonData::getInstance()->playerEntities;
		float finalDist = FLT_MAX;

		
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


				Vector3 diff = thePlayer->GetPos() - player.GetPos();
				float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
				if (dist <= 5) {
					if (finalDist > dist)
					{
						target = player;
						finalDist = (float)dist;
					}
				}

			}
		}

		if (!target.getInstance()) {
			return;
		}

		if (!(thePlayer->getHurtTime() > 0)) {
			if (this->blatent || this->ticks % (int)(this->tick * 10) == 0) {
				if (!this->blatent && this->bypass) {
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
					target.setPos(target.GetPos().x, target.GetPos().y, target.GetPos().z);
				}
				else {
					target.setPos(target.GetPrevPos().x, target.GetPrevPos().y, target.GetPrevPos().z);
					Blink::getInstance()->lag(ms);
				}
			}
		}
		
		this->ticks++;
		
	}
	else if (this->getMode() == 2) {
		prev_reach = ReachDistance;
		Patcher::put("reach_distance", std::to_string(ReachDistance));
	}

}

void Reach::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("reach", ImVec2(450, 75))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(962510894, "Toggle Reach", this);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		
		if (this->getMode() == 0 || this->getMode() == 2)
			ImGui::SliderFloat("Reach Distance", &this->ReachDistance, 0, 6);
		if (this->getMode() == 1) {
			//ImGui::SliderFloat("Backtrack Ticks", &this->ticks, 0, 15);
			ImGui::Checkbox("Blatent", &this->blatent);
			if (!this->blatent) {
				ImGui::SliderFloat("Ticks", &this->tick, 1, 30);
				ImGui::SliderFloat("Lag Ms", &this->ms, 1, 1000);
				ImGui::Checkbox("Ghost", &this->bypass);
			}

		}
		ImGui::Text("Reach Mode");
		ImGui::Combo("Re", &this->getMode(), this->modes, 3);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
