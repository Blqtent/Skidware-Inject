#include "jhook.h"
#include "../../../ext/jni/jni.h"
#include "../../../ext/minhook/minhook.h"
#include "../java/java.h"
#include "../sdk/JNIHelper.h"
#include "../moduleManager/modules/player/eagle.h"
#include "../util/logger.h"
typedef void(__cdecl* mvEntity) (double, double, double);

mvEntity pMoveEntity;
mvEntity pMoveEntityarget;

void __cdecl pmvEntity(double x, double y, double z) {
    if (Eagle::getInstance()->safewalk && Eagle::getInstance()->blockmovement) {

        Eagle::getInstance()->blockmovement = false;
        return pMoveEntity(0, y, 0);

    }
    return pMoveEntity(x, y, z);
}

bool jhook::apply_moveEntityHook() {
    jclass player_class;
    Java::AssignClass("net.minecraft.entity.Entity", player_class);
    jmethodID method = Java::Env->GetMethodID(player_class, JNIHelper::IsForge() ? "func_70091_d" : "moveEntity", "(DDD)V");
    pMoveEntityarget = reinterpret_cast<mvEntity>(*(unsigned __int64*)(*(unsigned __int64*)method + 0x40));

    MH_STATUS status = MH_CreateHook(reinterpret_cast<void**>(pMoveEntityarget), &pmvEntity, reinterpret_cast<void**>(&pMoveEntity));
    if (status != MH_OK) {
        //wrapper::output("failed to hook moveEntity");
        //wrapper::output(MH_StatusToString(status));
        Logger::Log("Failed MoveEntity");
        return false;
    }
    if (MH_EnableHook(reinterpret_cast<void**>(pMoveEntityarget)) != MH_OK) {
        //wrapper::output("failed to enable moveEntity hook");
        Logger::Log("Failed MoveEntity");
        return false;
    }

    Java::Env->DeleteLocalRef(player_class);

    //wrapper::output("moveEntity hooked");
    Logger::Log("Hooked MoveEntity");

    return true;
}
