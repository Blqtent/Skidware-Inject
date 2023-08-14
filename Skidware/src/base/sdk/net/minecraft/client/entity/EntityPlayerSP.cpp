#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"
#include "../../../../../moduleManager/commonData.h"

CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
	Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", this->Class);
}

jclass CEntityPlayerSP::GetClass()
{
	return this->Class;
}

jobject CEntityPlayerSP::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
}

void CEntityPlayerSP::setSneak(bool state)
{
	if (JNIHelper::IsForge()) {
		CGameSettings* settings = SDK::Minecraft->gameSettings;

		jfieldID sneak = Java::Env->GetFieldID(settings->GetClass(), "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");
		jobject sneakObj = Java::Env->GetObjectField(settings->GetInstance(), sneak);
		jclass keybind_class = Java::Env->GetObjectClass(sneakObj);

		jfieldID pressed = Java::Env->GetFieldID(keybind_class, "field_74513_e", "Z");

		Java::Env->SetBooleanField(sneakObj, pressed, state);
		return;
	}
	CGameSettings* settings = SDK::Minecraft->gameSettings;

	jfieldID sneak = Java::Env->GetFieldID(settings->GetClass(), "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");
	jobject sneakObj = Java::Env->GetObjectField(settings->GetInstance(), sneak);
	jclass keybind_class = Java::Env->GetObjectClass(sneakObj);

	jfieldID pressed = Java::Env->GetFieldID(keybind_class, "pressed", "Z");

	Java::Env->SetBooleanField(sneakObj, pressed, state);
	
}

void CEntityPlayerSP::attackEntity(CEntityPlayerSP* player, jobject entity)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		jobject playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78764_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V");
		return Java::Env->CallVoidMethod(playerControllerObj, attackMid, player->GetInstance(), entity);
	}
	jobject playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "attackEntity", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity /Entity;)V");
	return Java::Env->CallVoidMethod(playerControllerObj, attackMid, player->GetInstance(), entity);
}

bool CEntityPlayerSP::sendUseItem(CEntityPlayer* player, CWorld* world, CItemStack item)
{
	jclass playerControllerClazz;
	Java::AssignClass("net.minecraft.client.multiplayer.PlayerControllerMP", playerControllerClazz);
	if (JNIHelper::IsForge()) {
		jobject playerControllerObj = SDK::Minecraft->getPlayerController();
		jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "func_78769_a", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
		return Java::Env->CallBooleanMethod(playerControllerObj, attackMid, player->GetInstance(), world, item.GetInstance());
	}
	jobject playerControllerObj = SDK::Minecraft->getPlayerController();
	jmethodID attackMid = Java::Env->GetMethodID(playerControllerClazz, "sendUseItem", "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/world/World;Lnet/minecraft/item/ItemStack;)Z");
	return Java::Env->CallBooleanMethod(playerControllerObj, attackMid, player->GetInstance(), world, item.GetInstance());
}

double CEntityPlayerSP::get_motion_x()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70159_w" : "motionX", "D");
	double x = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionX);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return x;
}

void CEntityPlayerSP::set_motion_x(double x)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionX, (jdouble)x);
	JNIHelper::env->DeleteLocalRef(playerclass);
}

double CEntityPlayerSP::get_motion_y()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	double y = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionY);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return y;
}

void CEntityPlayerSP::set_motion_y(double y)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID yfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70181_x" : "motionY", "D");
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionY, (jdouble)y);
	JNIHelper::env->DeleteLocalRef(playerclass);
}

double CEntityPlayerSP::get_motion_z()
{
	if (GetClass() == NULL) return NULL;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70179_y" : "motionZ", "D");
	double z = (double)JNIHelper::env->GetDoubleField(GetInstance(), StrayCache::entity_motionZ);
	JNIHelper::env->DeleteLocalRef(playerclass);
	return z;
}

void CEntityPlayerSP::set_motion_z(double z)
{
	if (GetClass() == NULL) return;
	jclass playerclass = JNIHelper::env->GetObjectClass(GetInstance());
	jfieldID xfid = JNIHelper::env->GetFieldID(playerclass, JNIHelper::IsForge() ? "field_70179_y" : "motionZ", "D");
	JNIHelper::env->SetDoubleField(GetInstance(), StrayCache::entity_motionZ, (jdouble)z);
	JNIHelper::env->DeleteLocalRef(playerclass);
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

jobject CEntityPlayerSP::get_abilities()
{
	if (JNIHelper::IsForge()) {
		jfieldID abi = Java::Env->GetFieldID(this->GetClass(), "field_71075_bZ", "Lnet/minecraft/entity/player/PlayerAbilities;");
		return Java::Env->GetObjectField(this->GetInstance(), abi);
	}
	jfieldID abi = Java::Env->GetFieldID(this->GetClass(), "abilities", "Lnet/minecraft/entity/player/PlayerAbilities;");
	return Java::Env->GetObjectField(this->GetInstance(), abi);
}

void CEntityPlayerSP::setFly(bool state)
{
	jclass clazz;
	Java::AssignClass("net.minecraft.entity.player.PlayerCapabilities", clazz);
	if (JNIHelper::IsForge()) {
		jfieldID abi = Java::Env->GetFieldID(clazz, "field_75100_b", "Z");
		return Java::Env->SetBooleanField(get_abilities(), abi, state);
	}
	jfieldID abi = Java::Env->GetFieldID(clazz, "isFlying", "Z");
	return Java::Env->SetBooleanField(get_abilities(), abi, state);

}


void CEntityPlayerSP::sendGroundPacket(jobject Packet)
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
	jobject queueObject = Java::Env->GetObjectField(GetInstance(), fieldQueue);
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

	Java::Env->CallVoidMethod(queueObject, addToSendQueue, Packet);

	Java::Env->DeleteLocalRef(playerClass);

	Java::Env->DeleteLocalRef(queueObject);

	Java::Env->DeleteLocalRef(playerHandler);


	return;
}

jobject CEntityPlayerSP::C03PacketPlayer(jboolean ground, float yaw, float pitch)
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
	return Packet;
}
