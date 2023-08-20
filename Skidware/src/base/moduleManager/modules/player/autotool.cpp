#include "autotool.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"
#include "../../../sdk/net/minecraft/item/ItemStack.h"
#include "../../../sdk/net/minecraft/block/Block.h"
#include "../../../sdk/net/minecraft/block/state/IBlockState.h"
#include "../../../sdk/net/minecraft/util/MovingObjectPosition.h"
#include "../../../sdk/net/minecraft/entity/player/InventoryPlayer.h"
#include "../../../sdk/net/minecraft/item/ItemTool.h"
#include <iostream>

AutoTool::AutoTool() : AbstractModule("AutoTool", Category::PLAYER) {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

AutoTool* AutoTool::getInstance() {
	static auto* inst = new AutoTool();
	return inst;
}

void AutoTool::onDisable() {
}

void AutoTool::onEnable() {
}

void AutoTool::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (CommonData::getInstance()->isCombat) return;
	if (GetAsyncKeyState(VK_RBUTTON) && 1) return;
	if (!GetAsyncKeyState(VK_LBUTTON) && 1) {
		SDK::Minecraft->thePlayer->GetInventory().SetCurrentItem(currentSlot);
		return;
	}
	if (GetAsyncKeyState(VK_LBUTTON) && 1) {
		float bestSpeed = 1.f;
		int bestSlot = -1;
		CMovingObjectPosition mouseover = SDK::Minecraft->GetMouseOver();
		if (mouseover.IsTypeOfEntity())
			return;
		//Logger::LogWait("hI", 1);

		if (!mouseover)
		{
			return;
		}

		//Logger::Log("MouseOver finished");

		BlockPos blockpos = mouseover.getBlockPos();

		if (!blockpos)
		{
			return;
		}
		//Logger::Log("blockpos finished");
		if (SDK::Minecraft->theWorld->isAirBlock(blockpos))
		{
			return;
		}
		CIBlockState blockstate = SDK::Minecraft->theWorld->getBlockState(blockpos);

		if (!blockstate)
		{
			return;
		}

		//Logger::Log("blockstate finished");
		CBlock block = blockstate.getBlock();

		if (!block)
		{
			return;
		}

		//Logger::Log("block finished"); 
	
		auto inventory = SDK::Minecraft->thePlayer->GetInventory();

		for (int i = 0; i <= 8; i++)
		{
			if (!inventory.isValid() || inventory.isNULL()) continue;
			auto item = inventory.GetStackInSlot(i);
			if (!item || item.isNULL()) continue;
			if (block.isNULL()) continue;
			/*if (Java::Env->IsInstanceOf(item.getInstance(),StrayCache::itemTool_class))
			{
				float speed = CItemTool(item.GetItem().getInstance()).GetStrVsBlock(item, block);
			}else{
				float speed = item.GetStrVsBlock(block);
			}*/


			float speed = item.GetStrVsBlock(block);
			
			/*Logger::Log("OK?");*/
			if (speed > bestSpeed) {
				bestSpeed = speed;
				bestSlot = i;
			}
		}
		if (bestSlot == -1)
		{
			return;
		}
		currentSlot = inventory.GetCurrentItemIndex();
		inventory.SetCurrentItem(bestSlot);
	}
	
}

void AutoTool::RenderMenu()
{
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("AutoTool", ImVec2(450, 100))) {

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(1231231245, "Toggle AutoTool", this);
		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}
