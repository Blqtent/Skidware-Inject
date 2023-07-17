#pragma once

struct Base
{
	static void Init();
	static void Kill();

	static void CheatLoop();
	static void RenderLoop();

	static inline bool Running;

	//1 = Lunar, 2 = Forge, 3 = Vanilla/Badlion

};

