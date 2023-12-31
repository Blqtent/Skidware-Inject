#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"
#include "../../../../../moduleManager/commonData.h"

//CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
//{
//	Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", this->Class);
//	if (this->Class = nullptr)
//	{
//		if (!StrayCache::initialized) StrayCache::Initialize();
//		this->Class = StrayCache::gamesettings_class;
//	}
//}
//
//jclass CEntityPlayerSP::getClass()
//{
//	return this->Class;
//}
//
//jobject CEntityPlayerSP::getInstance()
//{
//	return Java::Env->GetObjectField(SDK::Minecraft->getInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
//}

void CEntityPlayerSP::setSneak(bool state)
{
	CGameSettings* settings = SDK::Minecraft->gameSettings;
	jobject sneakObj = Java::Env->GetObjectField(settings->getInstance(), StrayCache::gamesettings_keyBindSneak);
	jclass keybind_class = Java::Env->GetObjectClass(sneakObj);
	jfieldID pressed;
	if (JNIHelper::IsForge())
		pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
	else
		pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");

	Java::Env->SetBooleanField(sneakObj, pressed, state);
}

void CEntityPlayerSP::setKeyJump(bool state)
{
	CGameSettings* settings = SDK::Minecraft->gameSettings;
	jobject sneakObj = Java::Env->GetObjectField(settings->getInstance(), StrayCache::gamesettings_keyBindJump);
	jclass keybind_class = Java::Env->GetObjectClass(sneakObj);
	jfieldID pressed;
	if (JNIHelper::IsForge())
		pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");
	else
		pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");

	Java::Env->SetBooleanField(sneakObj, pressed, state);
}

void CEntityPlayerSP::attackEntity(CEntityPlayerSP* player, jobject entity)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		Object playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		return Java::Env->CallVoidMethod(playerControllerObj.getInstance(), attackMid, player->getInstance(), entity);
	}
	Object playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
	return Java::Env->CallVoidMethod(playerControllerObj.getInstance(), attackMid, player->getInstance(), entity);
}

bool CEntityPlayerSP::sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		Object playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		return Java::Env->CallBooleanMethod(playerControllerObj.getInstance(), attackMid, player->getInstance(), world, item.getInstance());
	}
	Object playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
	return Java::Env->CallBooleanMethod(playerControllerObj.getInstance(), attackMid, player->getInstance(), world, item.getInstance());
}



double CEntityPlayerSP::toRadians(float degrees) {
	return degrees * (M_PI / 180);
}

float CEntityPlayerSP::get_direction()
{
	float yaw = SDK::Minecraft->thePlayer->GetRotationYaw();
	float strafe = 45;
	// add 180 to the yaw to strafe backwards
	if (SDK::Minecraft->thePlayer->getMoveForward() < 0) {
		// invert our strafe to -45
		strafe = -45;
		yaw += 180;
	}
	if (SDK::Minecraft->thePlayer->getMoveStrafe() > 0) {
		// subtract 45 to strafe left forward
		yaw -= strafe;
		// subtract an additional 45 if we do not press W in order to get to -90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw -= 45;
		}
	}
	else if (SDK::Minecraft->thePlayer->getMoveStrafe() < 0) {
		// add 45 to strafe right forward
		yaw += strafe;
		// add 45 if we do not press W in order to get to 90
		if (SDK::Minecraft->thePlayer->getMoveForward() == 0) {
			yaw += 45;
		}
	}
	return yaw;
}

float CEntityPlayerSP::get_speed()
{
	Vector3 velocity_vector = SDK::Minecraft->thePlayer->getMotion();

	return sqrt(velocity_vector.x * velocity_vector.x + velocity_vector.z * velocity_vector.z);
}

bool CEntityPlayerSP::isStrafing() {
	return SDK::Minecraft->thePlayer->getMoveStrafe() != 0;
}

bool CEntityPlayerSP::isMovingForwardsOrBackwards() {
	return SDK::Minecraft->thePlayer->getMoveForward() != 0;
}

bool CEntityPlayerSP::isMovingForwards()
{
	return SDK::Minecraft->thePlayer->getMoveForward() > 0;

}

bool CEntityPlayerSP::isMovingBackwards()
{
	return SDK::Minecraft->thePlayer->getMoveForward() < 0;

}

void CEntityPlayerSP::set_speed(const float speed)
{
	if (getMotion().x != 0 && getMotion().y != 0) {
		double yaw = toRadians(get_direction());
		float y = SDK::Minecraft->thePlayer->getMotion().y;
		float x = -sin(yaw) * speed;
		float z = cos(yaw) * speed;
		SDK::Minecraft->thePlayer->setMotion(Vector3(x, 100000000000, z));
	}
}

Object CEntityPlayerSP::get_abilities()
{
	if (JNIHelper::IsForge()) {
		jfieldID abi = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71075_bZ", "Lnet/minecraft/entity/player/PlayerAbilities;");
		return Java::Env->GetObjectField(this->getInstance(), abi);
	}
	jfieldID abi = Java::Env->GetFieldID(this->getClass(), "capabilities", "Lnet/minecraft/entity/player/PlayerAbilities;");
	return Object(Java::Env->GetObjectField(this->getInstance(), abi));
}

void CEntityPlayerSP::setFly(bool state)
{
	jclass clazz;
	Java::AssignClass("net.minecraft.entity.player.PlayerCapabilities", clazz);
	if (JNIHelper::IsForge()) {
		jfieldID abi = Java::Env->GetFieldID(clazz, "field_75100_b", "Z");
		return Java::Env->SetBooleanField(get_abilities().getInstance(), abi, state);
	}
	jfieldID abi = Java::Env->GetFieldID(clazz, "isFlying", "Z");
	return Java::Env->SetBooleanField(get_abilities().getInstance(), abi, state);

}

void CEntityPlayerSP::sendPacket(Object Packet)
{
	jclass playerClass;
	Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", playerClass);
	jclass playerHandler;
	Java::AssignClass("net.minecraft.client.network.NetHandlerPlayClient", playerHandler);
	jfieldID fieldQueue;
	if (JNIHelper::IsForge())
		fieldQueue = Java::Env->GetFieldID(playerClass, "field_71174_a", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
	else
		fieldQueue = Java::Env->GetFieldID(playerClass, "sendQueue", "Lnet/minecraft/client/network/NetHandlerPlayClient;");
	jobject queueObject = Java::Env->GetObjectField(getInstance(), fieldQueue);
	if (fieldQueue == nullptr) {
		//std::cout << "[!] Queue object not found !" << std::endl;
		return;
	}
	jmethodID addToSendQueue;

	if (JNIHelper::IsForge())
		addToSendQueue = Java::Env->GetMethodID(playerHandler, "func_147297_a", "(Lnet/minecraft/network/Packet;)V");
	else
		addToSendQueue = Java::Env->GetMethodID(playerHandler, "addToSendQueue", "(Lnet/minecraft/network/Packet;)V");

	if (addToSendQueue == nullptr) {
		//std::cout << "[!] Method addToQueue not found !" << std::endl;
		return;
	}

	Java::Env->CallVoidMethod(queueObject, addToSendQueue, Packet.getInstance());

	Java::Env->DeleteLocalRef(playerClass);

	Java::Env->DeleteLocalRef(queueObject);

	Java::Env->DeleteLocalRef(playerHandler);


	return;
}

Object CEntityPlayerSP::C03PacketPlayer(jboolean ground, float yaw, float pitch)
{
	jclass C03;
	Java::AssignClass("net.minecraft.network.play.client.C03PacketPlayer", C03);
	jmethodID c03Constructer = Java::Env->GetMethodID(C03, "<init>", "(Z)V");
	jfieldID yawf, pitchf;
	if (JNIHelper::IsForge()) {
		yawf = Java::Env->GetFieldID(C03, "field_149476_e", "F");
		pitchf = Java::Env->GetFieldID(C03, "field_149473_f", "F");
	}
	else {
		yawf = Java::Env->GetFieldID(C03, "yaw", "F");
		pitchf = Java::Env->GetFieldID(C03, "pitch", "F");
	}
	jobject Packet = Java::Env->NewObject(C03, c03Constructer, ground);
	Java::Env->SetFloatField(Packet, yawf, yaw);
	Java::Env->SetFloatField(Packet, pitchf, pitch);
	return Object(Packet);
}

Object CEntityPlayerSP::C04PacketPos(double x, double y, double z, bool g)
{

	jclass C04;
	Java::AssignClass("net.minecraft.network.play.client.C03PacketPlayer$C04PacketPlayerPosition", C04);
	jmethodID c04Constructer = Java::Env->GetMethodID(C04, "<init>", "(DDDZ)V");
	//jfieldID yawf, pitchf;
	jobject Packet = Java::Env->NewObject(C04, c04Constructer, x, y, z, g);
	return Object(Packet);
}

Object CEntityPlayerSP::C05PacketLook(float yaw, float pitch, bool g)
{

	jclass C04;
	Java::AssignClass("net.minecraft.network.play.client.C03PacketPlayer$C05PacketPlayerLook", C04);
	jmethodID c04Constructer = Java::Env->GetMethodID(C04, "<init>", "(FFZ)V");
	//jfieldID yawf, pitchf;
	jobject Packet = Java::Env->NewObject(C04, c04Constructer, yaw, pitch, g);
	return Object(Packet);
}