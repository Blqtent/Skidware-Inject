#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>
#include "../../commonData.h"
class Cavefinder : public AbstractModule
{
public:
    static Cavefinder* getInstance();
    void onEnable();
    void onDisable();
    void RenderMenu();
private:
    Cavefinder();
};