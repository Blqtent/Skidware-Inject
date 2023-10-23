#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <vector>
#include <string>
class Esp :public AbstractModule {
public:
    static Esp* getInstance();
    void onEnable();
    void onDisable();
    void onUpdate(const EventUpdate e);
    void RenderUpdate();
    void RenderMenu();

    struct Data {
        std::vector<Vector3> boxVerticies;
        std::string name;
        std::string distText;
        float dist;
        float opacityFadeFactor;
        float health;
        float maxHealth;
        Vector3 pos;
    };
    std::vector<Data> renderData;
    
    bool Box = true;
    float BoxColor[4]{ 255, 255, 255, 1 };

    bool FilledBox = true;
    float FilledBoxColor[3]{ 0, 0, 0 };
    float SecondFilledBoxColor[3]{ 0, 0, 0 };
    float FilledBoxOpacity = 0.15f;

    bool Outline = true;
    float OutlineColor[4]{ 0, 0, 0, 0.25 };

    bool Text = true;
    float TextSize = 18;
    float TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };

    bool TestCircles = false;
    float TestCirclesColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };

    bool TextOutline = true;
    float TextOutlineColor[4]{ 0, 0, 0, 1.0f };
    float TextUnrenderDistance = 14.0f;

    float FadeDistance = 3.0f;

    bool HealthBar = true;
    bool targetHud = false;
private:
    Esp();
};