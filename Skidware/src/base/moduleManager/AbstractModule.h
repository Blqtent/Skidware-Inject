#pragma once

#include <string>
#include <windows.h>

#define IsKeyBeingDown(KEYNONAME) ((GetAsyncKeyState(KEYNONAME)&0x8000)?1:0)

enum class Category : unsigned int {
    BLATENT = 1,
    CLICKER,
    COMBAT,
    PLAYER,
    VISUAL
    //safeDestruct
};

class AbstractModule {

private:

    std::string name;
    int key = 0;
    Category category;
    bool i_toggle;
    //const char* desc; TODO
    int mode = 0;
public:
    void toggle();

    void onToggled();

    std::string getName();

    bool getToggle();

    void setToggle(bool _NEW);

    void enable();

    void disable();

    int& getKey();

    int& getMode();

    void setKeyCode(int keycode);

    void onKeyEvent(int key);

    Category getCategory();

    virtual void onEnable() = 0;

    virtual void onDisable() = 0;

    AbstractModule(const char *ModName, Category Modcategory);

    AbstractModule(const char *ModName, Category Modcategory, int k);

    virtual ~AbstractModule() = default;

    AbstractModule(AbstractModule &&) = delete;

    AbstractModule(const AbstractModule &) = delete;

    AbstractModule &operator=(const AbstractModule &) = delete;

};
