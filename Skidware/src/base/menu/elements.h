#pragma once

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"

namespace elements {
    bool tab(const char* name, bool boolean);
}
