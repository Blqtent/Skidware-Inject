#pragma once
#include "module.h"
#include <vector>

class ModuleManager
{
public:
	static void Init();

	static void UpdateModules();
public:
	static std::vector<module> mods;
};

