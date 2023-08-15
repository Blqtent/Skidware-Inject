#pragma once
#include "../java/java.h"
#include "JNIHelper.h"

struct StrayCache {

	inline static bool initialized;

	// ENTITY CLASS
	inline static jclass entity_class;
	inline static jmethodID entity_getName;
	inline static jmethodID entity_isSneaking;
	inline static jmethodID entity_setSneaking;
	inline static jmethodID entity_setPosition;
	inline static jmethodID entity_setSprint;
	inline static jmethodID entity_isInvisible;
	inline static jmethodID entity_inWater;
	inline static jfieldID entity_posX;
	inline static jfieldID entity_posY;
	inline static jfieldID entity_posZ;
	inline static jfieldID entity_lastTickPosX;
	inline static jfieldID entity_lastTickPosY;
	inline static jfieldID entity_lastTickPosZ;
	inline static jfieldID entity_width;
	inline static jfieldID entity_height;
	inline static jfieldID entity_distanceWalkedModified;
	inline static jfieldID entity_prevDistanceWalkedModified;
	inline static jfieldID entity_rotationYaw;
	inline static jfieldID entity_rotationPitch;
	inline static jfieldID entity_prevRotationYaw;
	inline static jfieldID entity_prevRotationPitch;
	inline static jfieldID entity_boundingBox;
	inline static jfieldID entity_motionX;
	inline static jfieldID entity_motionY;
	inline static jfieldID entity_motionZ;
	inline static jfieldID entity_onGround;
	inline static jfieldID entity_fallDistance;
	inline static jfieldID entity_ticksExisted;
	inline static jfieldID entity_isDead;

	// ENTITY LIVING BASE CLASS
	inline static jclass entityLivingBase_class;
	inline static jmethodID entityLivingBase_getHealth;
	inline static jmethodID entityLivingBase_getMaxHealth;
	inline static jmethodID entityLivingBase_canEntityBeSeen;
	inline static jmethodID entityLivingBase_swingItem;
	inline static jmethodID entityLivingBase_jump;
	inline static jfieldID entityLivingBase_hurttime;
	inline static jfieldID entityLivingBase_moveForward;
	inline static jfieldID entityLivingBase_moveStrafe;

	//Entity Player
	inline static jclass entityPlayer_class;

	//Entity Player SP
	inline static jclass entityPlayerSP_class;

	//Game Settings
	inline static jclass gamesettings_class;

	//World Client
	inline static jclass worldClient_class;

	//ActiveRenderInfo
	inline static jclass activeRenderInfo_class;
	
	//RenderManager
	inline static jclass renderManager_class;
	
	//Timer
	inline static jclass timer_class;

	//World
	inline static jclass world_class;
	
	//World
	inline static jclass chunk_class;


	
	

	// AXIS ALIGNED BB CLASS
	inline static jclass axisAlignedBB_class;
	inline static jfieldID axisAlignedBB_minX;
	inline static jfieldID axisAlignedBB_minY;
	inline static jfieldID axisAlignedBB_minZ;
	inline static jfieldID axisAlignedBB_maxX;
	inline static jfieldID axisAlignedBB_maxY;
	inline static jfieldID axisAlignedBB_maxZ;

	// MOVING OBJECT POSITION CLASS
	inline static jclass movingObjectPosition_class;
	inline static jfieldID movingObjectPosition_hitVec;
	inline static jfieldID movingObjectPosition_typeOfHit;
	inline static jfieldID movingObjectPosition_blockPos;

	inline static jclass vec3_class;
	inline static jfieldID vec3_xCoord;
	inline static jfieldID vec3_yCoord;
	inline static jfieldID vec3_zCoord;

	inline static jclass inventoryPlayer_class;
	inline static jmethodID inventoryPlayer_getCurrentItem;
	inline static jfieldID inventoryPlayer_mainInv;
	inline static jfieldID inventoryPlayer_currentItem;

	inline static jclass itemStack_class;
	inline static jmethodID itemStack_getItem;
	inline static jmethodID itemStack_getItemID;
	inline static jclass blockPos_class;
	inline static jfieldID blockPos_x;
	inline static jfieldID blockPos_y;
	inline static jfieldID blockPos_z;

	static void Initialize() {
		/*
		if (JNIHelper::IsVanilla()) {
			
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_getName = Java::Env->GetMethodID(entity_class, "e_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "av", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "c", "(Z)V");
			entity_posX = Java::Env->GetFieldID(entity_class, "s", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "t", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "u", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "P", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "Q", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "R", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "J", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "K", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "M", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "L", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "y", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "z", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "A", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "B", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "f", "Laug;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "v", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "w", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "x", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "C", "Z");

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "bn", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "bu", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "t", "(Lpk;)Z");
			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "au", "I");

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "f", "D");

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "c", "Laui;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "a", "Lauh$a;");

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "c", "D");

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "h", "()Lzx;");

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "b", "()Lzw;");

			initialized = true;
			return;
		}
		*/

		if (JNIHelper::IsForge()) {
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "func_70093_af", "()Z");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
			entity_posX = Java::Env->GetFieldID(entity_class, "field_70165_t", "D");
			entity_posY = Java::Env->GetFieldID(entity_class, "field_70163_u", "D");
			entity_posZ = Java::Env->GetFieldID(entity_class, "field_70161_v", "D");
			entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "field_70142_S", "D");
			entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "field_70137_T", "D");
			entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "field_70136_U", "D");
			entity_width = Java::Env->GetFieldID(entity_class, "field_70130_N", "F");
			entity_height = Java::Env->GetFieldID(entity_class, "field_70131_O", "F");
			entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70140_Q", "F");
			entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "field_70141_P", "F");
			entity_rotationYaw = Java::Env->GetFieldID(entity_class, "field_70177_z", "F");
			entity_rotationPitch = Java::Env->GetFieldID(entity_class, "field_70125_A", "F");
			entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "field_70126_B", "F");
			entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "field_70127_C", "F");
			entity_boundingBox = Java::Env->GetFieldID(entity_class, "field_70121_D", "Lnet/minecraft/util/AxisAlignedBB;");
			entity_motionX = Java::Env->GetFieldID(entity_class, "field_70159_w", "D");
			entity_motionY = Java::Env->GetFieldID(entity_class, "field_70181_x", "D");
			entity_motionZ = Java::Env->GetFieldID(entity_class, "field_70179_y", "D");
			entity_onGround = Java::Env->GetFieldID(entity_class, "field_70122_E", "Z");
			entity_fallDistance = Java::Env->GetFieldID(entity_class, "field_70143_R", "F");
			entity_ticksExisted = Java::Env->GetFieldID(entity_class, "field_70173_aa", "F");
			entity_isDead = Java::Env->GetFieldID(entity_class, "field_70128_L", "Z");
			entity_setSprint = Java::Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "func_70090_H", "()Z");

			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);

			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);

			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);

			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);

			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);

			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);

			Java::AssignClass("net.minecraft.util.Timer", timer_class);

			Java::AssignClass("net.minecraft.world.World", world_class);

			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);

			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");

			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");

			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "field_72450_a", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "field_72448_b", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "field_72449_c", "D");

			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");

			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
			itemStack_getItemID = Java::Env->GetMethodID(itemStack_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");

			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "field_177962_a", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "field_177960_b", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "field_177961_c", "I");


			initialized = true;
			return;
		}

		Java::AssignClass("net.minecraft.entity.Entity", entity_class);
		entity_getName = Java::Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
		entity_isSneaking = Java::Env->GetMethodID(entity_class, "isSneaking", "()Z");
		entity_setPosition = Java::Env->GetMethodID(entity_class, "setPosition", "(DDD)V");
		entity_setSneaking = Java::Env->GetMethodID(entity_class, "setSneaking", "(Z)V");
		entity_posX = Java::Env->GetFieldID(entity_class, "posX", "D");
		entity_posY = Java::Env->GetFieldID(entity_class, "posY", "D");
		entity_posZ = Java::Env->GetFieldID(entity_class, "posZ", "D");
		entity_lastTickPosX = Java::Env->GetFieldID(entity_class, "lastTickPosX", "D");
		entity_lastTickPosY = Java::Env->GetFieldID(entity_class, "lastTickPosY", "D");
		entity_lastTickPosZ = Java::Env->GetFieldID(entity_class, "lastTickPosZ", "D");
		entity_width = Java::Env->GetFieldID(entity_class, "width", "F");
		entity_height = Java::Env->GetFieldID(entity_class, "height", "F");
		entity_distanceWalkedModified = Java::Env->GetFieldID(entity_class, "distanceWalkedModified", "F");
		entity_prevDistanceWalkedModified = Java::Env->GetFieldID(entity_class, "prevDistanceWalkedModified", "F");
		entity_rotationYaw = Java::Env->GetFieldID(entity_class, "rotationYaw", "F");
		entity_rotationPitch = Java::Env->GetFieldID(entity_class, "rotationPitch", "F");
		entity_prevRotationYaw = Java::Env->GetFieldID(entity_class, "prevRotationYaw", "F");
		entity_prevRotationPitch = Java::Env->GetFieldID(entity_class, "prevRotationPitch", "F");
		entity_boundingBox = Java::Env->GetFieldID(entity_class, "boundingBox", "Lnet/minecraft/util/AxisAlignedBB;");
		entity_motionX = Java::Env->GetFieldID(entity_class, "motionX", "D");
		entity_motionY = Java::Env->GetFieldID(entity_class, "motionY", "D");
		entity_motionZ = Java::Env->GetFieldID(entity_class, "motionZ", "D");
		entity_onGround = Java::Env->GetFieldID(entity_class, "onGround", "Z");
		entity_fallDistance = Java::Env->GetFieldID(entity_class, "fallDistance", "F");
		entity_isDead = Java::Env->GetFieldID(entity_class, "isDead", "Z");
		entity_isInvisible = Java::Env->GetMethodID(entity_class, "isInvisible", "()Z");
		entity_ticksExisted = Java::Env->GetFieldID(entity_class, "ticksExisted", "F");
		entity_inWater = Java::Env->GetMethodID(entity_class, "inWater", "()Z");

		Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
		entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
		entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
		entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
		entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "hurtTime", "I");
		entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "moveForward", "I");
		entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "moveStrafing", "I");
		entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");
		entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "jump", "()V");

		Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
		axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "minX", "D");
		axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "minY", "D");
		axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
		axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
		axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
		axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");

		Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
		movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
		movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "blockPos", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");

		Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
		vec3_xCoord = Java::Env->GetFieldID(vec3_class, "xCoord", "D");
		vec3_yCoord = Java::Env->GetFieldID(vec3_class, "yCoord", "D");
		vec3_zCoord = Java::Env->GetFieldID(vec3_class, "zCoord", "D");

		Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
		inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");
		inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
		inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "currentItem", "I");

		Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
		itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
		itemStack_getItemID = Java::Env->GetStaticMethodID(itemStack_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");

		Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
		blockPos_x = Java::Env->GetFieldID(blockPos_class, "x", "I");
		blockPos_y = Java::Env->GetFieldID(blockPos_class, "y", "I");
		blockPos_z = Java::Env->GetFieldID(blockPos_class, "z", "I");
		initialized = true;
	}

	static void DeleteRefs() {
		Java::Env->DeleteLocalRef(entity_class);
		Java::Env->DeleteLocalRef(entityLivingBase_class);
		Java::Env->DeleteLocalRef(axisAlignedBB_class);
		Java::Env->DeleteLocalRef(movingObjectPosition_class);
		Java::Env->DeleteLocalRef(vec3_class);
	}
};