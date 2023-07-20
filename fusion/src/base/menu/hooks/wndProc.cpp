#include "../menu.h"

#include "../../../../ext/imgui/imgui_impl_win32.h"
#include "../../moduleManager/modules/visual/esp.h"
#include "../../moduleManager/modules/combat/aimAssist.h"
#include "../../moduleManager/modules/combat/reach.h"
#include "../../moduleManager/modules/clicker/leftAutoClicker.h"
#include "../../moduleManager/modules/clicker/rightAutoClicker.h"
#include "../../moduleManager/modules/combat/velocity.h"
#include "../../moduleManager/modules/player/fastplace.h"
#include "../../moduleManager/modules/player/eagle.h"
#include "../../moduleManager/modules/blatent/killaura.h"
#include "../../moduleManager/modules/blatent/Strafe.h"
#include "../../moduleManager/modules/blatent/nofall.h"
#include "../../moduleManager/modules/player/blink.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef LRESULT(CALLBACK* template_WndProc) (HWND, UINT, WPARAM, LPARAM);
template_WndProc original_wndProc;
LRESULT CALLBACK hook_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
	{
		if (wParam == Menu::Keybind)
			Menu::Open = !Menu::Open;
		if (wParam == VK_ESCAPE && Menu::Open)
			Menu::Open = false;			
		if (!SDK::Minecraft->IsInGuiState()) {
			if (wParam == Eagle::bind)
				Eagle::Enabled = !Eagle::Enabled;
			if (wParam == Killaura::bind)
				Killaura::Enabled = !Killaura::Enabled;
			if (wParam == Strafe::bind)
				Strafe::Enabled = !Strafe::Enabled;
			if (wParam == Fastplace::bind)
				Fastplace::Enabled = !Fastplace::Enabled;
			if (wParam == LeftAutoClicker::bind)
				LeftAutoClicker::Enabled = !LeftAutoClicker::Enabled;
			if (wParam == RightAutoClicker::bind)
				RightAutoClicker::Enabled = !RightAutoClicker::Enabled;
			if (wParam == AimAssist::bind)
				AimAssist::Enabled = !AimAssist::Enabled;
			if (wParam == Velocity::bind)
				Velocity::Enabled = !Velocity::Enabled;
			if (wParam == Reach::bind)
				Reach::Enabled = !Reach::Enabled;
			if (wParam == Esp::bind)
				Esp::Enabled = !Esp::Enabled;
			if (wParam == Nofall::bind)
				Nofall::Enabled = !Nofall::Enabled;
		}
	}

	if (Menu::Open && Menu::Initialized)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(original_wndProc, hwnd, msg, wParam, lParam);
}

void Menu::Hook_wndProc()
{
	original_wndProc = (template_WndProc)SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)hook_WndProc);
}

void Menu::Unhook_wndProc()
{
	SetWindowLongPtr(Menu::HandleWindow, GWLP_WNDPROC, (LONG_PTR)original_wndProc);
}