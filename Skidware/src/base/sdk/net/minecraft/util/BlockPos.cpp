#include "BlockPos.h"
#include "../../../../util/logger.h"
BlockPos::BlockPos()
{
    if (!StrayCache::initialized) StrayCache::Initialize();
    this->Class = StrayCache::axisAlignedBB_class;

}

BlockPos::BlockPos(jobject instance)
{
    this->Instance = instance;

}

jclass BlockPos::GetClass()
{
    return this->Class;
}

jobject BlockPos::GetInstance()
{
    return this->Instance;
}

Vector3 BlockPos::getPos()
{
    if (this->GetInstance() == NULL) {
        return Vector3(NULL, NULL, NULL);
    }
    Logger::Log("getPos");
    jint x = Java::Env->GetIntField(this->GetInstance(), StrayCache::blockPos_x);
    jint y = Java::Env->GetIntField(this->GetInstance(), StrayCache::blockPos_y);
    jint z = Java::Env->GetIntField(this->GetInstance(), StrayCache::blockPos_z);
    return Vector3(x, y, z);
}

