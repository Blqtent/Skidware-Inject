#pragma once
#include "../java/java.h"
#include "JNIHelper.h"

struct StrayCache {

	inline static bool initialized;

	//Minecraft Class
	inline static jclass minecraft_class;
	inline static jmethodID minecraft_getMinecraft;
	inline static jmethodID minecraft_getRenderViewEntity;
	inline static jmethodID minecraft_clickMouse;
	inline static jmethodID minecraft_getDebugFPS;
	inline static jfieldID minecraft_thePlayer;
	inline static jfieldID minecraft_theWorld;
	inline static jfieldID minecraft_playerController;
	inline static jfieldID minecraft_renderManager;
	inline static jfieldID minecraft_timer;
	inline static jfieldID minecraft_gameSettings;
	inline static jfieldID minecraft_currentScreen;
	inline static jfieldID minecraft_objectMouseOver;
	inline static jfieldID minecraft_rightClickDelayTimer;

	//ActiveRenderInfo Class
	inline static jclass activeRenderInfo_class;
	inline static jfieldID activeRenderInfo_MODELVIEW;
	inline static jfieldID activeRenderInfo_PROJECTION;


	//Game Settings
	inline static jclass gamesettings_class;
	inline static jmethodID gamesettings_setOptionKeyBinding;
	inline static jfieldID gamesettings_thirdPersonView;
	inline static jfieldID gamesettings_fovSetting;
	inline static jfieldID gamesettings_gammaSetting;
	inline static jfieldID gamesettings_keyBindFullscreen;
	inline static jfieldID gamesettings_keyBindSneak;


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
	inline static jmethodID entityLivingBase_isPlayerSleeping;
	inline static jmethodID entityLivingBase_swingItem;
	inline static jmethodID entityLivingBase_jump;
	inline static jfieldID entityLivingBase_hurttime;
	inline static jfieldID entityLivingBase_moveForward;
	inline static jfieldID entityLivingBase_moveStrafe;

	//Entity Player
	inline static jclass entityPlayer_class;
	inline static jfieldID entityPlayer_inventory;


	//Entity Player SP
	inline static jclass entityPlayerSP_class;
	inline static jfieldID entityPlayerSP_keyBindSneak;
	inline static jfieldID entityPlayerSP_pressed;
	inline static jfieldID entityPlayerSP_motionX;
	inline static jfieldID entityPlayerSP_motionY;
	inline static jfieldID entityPlayerSP_motionZ;
	inline static jfieldID entityPlayerSP_abilities;
	inline static jfieldID entityPlayerSP_isFlying;




	//World Client
	inline static jclass worldClient_class;
	inline static jfieldID worldClient_entityList;

	
	//RenderManager
	inline static jclass renderManager_class;
	inline static jfieldID renderManager_renderPosX;
	inline static jfieldID renderManager_renderPosY;
	inline static jfieldID renderManager_renderPosZ;
	inline static jfieldID renderManager_viewerPosX;
	inline static jfieldID renderManager_viewerPosY;
	inline static jfieldID renderManager_viewerPosZ;
	
	//Timer
	inline static jclass timer_class;
	inline static jfieldID timer_renderPartialTicks;
	inline static jfieldID timer_timerSpeed;


	//World
	inline static jclass world_class;
	inline static jmethodID world_rayTraceBlocks;
	inline static jmethodID world_getChunkFromChunkCoords;
	inline static jmethodID world_isAirBlock;
	inline static jfieldID world_playerEntities;
	//World
	inline static jclass chunk_class;
	inline static jmethodID chunk_getBlock;

	//collection
	inline static jclass conllection_class;
	inline static jmethodID conllection_toArray;

	//Set
	inline static jclass set_class;
	inline static jmethodID set_toArray;	
	
	//List
	inline static jclass list_class;
	inline static jmethodID list_toArray;

	//FloatBuffer
	inline static jclass floatBuffer_class;
	inline static jmethodID floatBuffer_get;

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
	inline static jfieldID inventoryPlayer_armorInv;
	inline static jfieldID inventoryPlayer_currentItem;

	inline static jclass itemStack_class;
	inline static jmethodID itemStack_getItem;
	inline static jmethodID itemStack_getIdFromItem;

	inline static jclass blockPos_class;
	inline static jfieldID blockPos_x;
	inline static jfieldID blockPos_y;
	inline static jfieldID blockPos_z;

	inline static jclass item_class;

	inline static jclass itemArmor_Class;
	inline static jmethodID itemArmor_getColor;

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
			{
				Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
				minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

				minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
				minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "func_175606_aa", "()Lnet/minecraft/entity/Entity;");
				minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "func_147116_af", "()V");
				minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "func_175610_ah", "()I");

				minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "field_71439_g", "Lnet/minecraft/client/entity/EntityPlayerSP;");
				minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "field_71441_e", "Lnet/minecraft/client/multiplayer/WorldClient;");
				minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "field_71442_b", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
				minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "field_175616_W", "Lnet/minecraft/client/renderer/entity/RenderManager;");
				minecraft_timer = Java::Env->GetFieldID(minecraft_class, "field_71428_T", "Lnet/minecraft/util/Timer;");
				minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "field_71474_y", "Lnet/minecraft/client/settings/GameSettings;");
				minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "field_71462_r", "Lnet/minecraft/client/gui/GuiScreen;");
				minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "field_71476_x", "Lnet/minecraft/util/MovingObjectPosition;");
				minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "field_71467_ac", "I");

			}

			{
				Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
				gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

				gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "func_151440_a", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
				gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74320_O", "I");
				gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74334_X", "F");
				gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_74333_Y", "F");
				gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "field_152395_am", "Lnet/minecraft/client/settings/KeyBinding;");
				gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "field_74311_E", "Lnet/minecraft/client/settings/KeyBinding;");
				
			}


			{
				Java::AssignClass("net.minecraft.entity.Entity", entity_class);
				entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

				entity_getName = Java::Env->GetMethodID(entity_class, "func_70005_c_", "()Ljava/lang/String;");
				entity_isSneaking = Java::Env->GetMethodID(entity_class, "func_70093_af", "()Z");
				entity_setSneaking = Java::Env->GetMethodID(entity_class, "func_70095_a", "(Z)V");
				entity_setPosition = Java::Env->GetMethodID(entity_class, "func_70107_b", "(DDD)V");
				entity_setSprint = Java::Env->GetMethodID(entity_class, "func_70031_b", "(Z)V");
				entity_isInvisible = Java::Env->GetMethodID(entity_class, "func_82150_aj", "()Z");
				entity_inWater = Java::Env->GetMethodID(entity_class, "func_70090_H", "()Z");

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

			}

			{
				Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
				entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

				entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110143_aJ", "()F");
				entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "func_110138_aP", "()F");
				entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "func_70685_l", "(Lnet/minecraft/entity/Entity;)Z");
				entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "func_70608_bn", "()Z");
				entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "func_71038_i", "()V");
				entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "func_70664_aZ", "()V");

				entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "field_70737_aN", "I");
				entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "field_70701_bs", "F");
				entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "field_70702_br", "F");

			}

			{
				Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
				entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);

				entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "field_71071_by", "Lnet/minecraft/entity/player/InventoryPlayer;");
			}


			Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
			entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
			

			{
				Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
				activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);

				activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178813_c", "Ljava/nio/FloatBuffer;");
				activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "field_178812_b", "Ljava/nio/FloatBuffer;");
			}
			

			{
				Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
				renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);

				renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "field_78725_b", "D");
				renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "field_78726_c", "D");
				renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "field_78723_d", "D");
				renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "field_78730_l", "D");
				renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "field_78731_m", "D");
				renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "field_78728_n", "D");
			}

			
			{
				Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
				worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

				worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "field_73032_d", "Ljava/util/Set;");

			}

			{
				Java::AssignClass("net.minecraft.world.World", world_class);
				world_class = (jclass)Java::Env->NewGlobalRef(world_class);

				world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "func_147447_a", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");

				world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "func_175623_d", "(Lnet/minecraft/util/BlockPos;)Z");
				world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "func_72964_e", "(II)Lnet/minecraft/world/chunk/Chunk;");

				world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "field_73010_i", "Ljava/util/List;");
			}

			{
				Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
				chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

				chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "func_177438_a", "(III)Lnet/minecraft/block/Block;");
			}
			


			{
				Java::AssignClass("net.minecraft.util.Timer", timer_class);
				timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

				timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "field_74278_d", "F");
				timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "field_74281_c", "F");

			}


			{
				Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
				axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

				axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72340_a", "D");
				axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72338_b", "D");
				axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72339_c", "D");
				axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "field_72336_d", "D");
				axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "field_72337_e", "D");
				axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "field_72334_f", "D");
			}

			{
				Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
				movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

				movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "field_72307_f", "Lnet/minecraft/util/Vec3;");
				movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "field_72313_a", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
				movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "field_178783_e", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			}
			
			{
				Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
				vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

				vec3_xCoord = Java::Env->GetFieldID(vec3_class, "field_72450_a", "D");
				vec3_yCoord = Java::Env->GetFieldID(vec3_class, "field_72448_b", "D");
				vec3_zCoord = Java::Env->GetFieldID(vec3_class, "field_72449_c", "D");
			}



			{
				Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
				inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

				inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "func_70448_g", "()Lnet/minecraft/item/ItemStack;");

				inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70462_a", "[Lnet/minecraft/item/ItemStack;");
				inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "field_70460_b", "[Lnet/minecraft/item/ItemStack;");
				inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "field_70461_c", "I");
			}

			{
				Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
				itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

				itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "func_77973_b", "()Lnet/minecraft/item/Item;");
				itemStack_getIdFromItem = Java::Env->GetMethodID(itemStack_class, "func_150891_b", "(Lnet/minecraft/item/Item;)I");
			}


			Java::AssignClass("net.minecraft.item.Item", item_class);
			item_class = (jclass)Java::Env->NewGlobalRef(item_class);


			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "func_82814_b", "(Lnet/minecraft/item/ItemStack;)I");

			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_class = (jclass)Java::Env->NewGlobalRef(blockPos_class);

			blockPos_x = Java::Env->GetFieldID(blockPos_class, "field_177962_a", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "field_177960_b", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "field_177961_c", "I");


			goto End;
		}


		//Lunar
		{
			Java::AssignClass("net.minecraft.client.Minecraft", minecraft_class);
			minecraft_class = (jclass)Java::Env->NewGlobalRef(minecraft_class);

			minecraft_getMinecraft = Java::Env->GetStaticMethodID(minecraft_class, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
			minecraft_getRenderViewEntity = Java::Env->GetMethodID(minecraft_class, "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
			minecraft_clickMouse = Java::Env->GetMethodID(minecraft_class, "clickMouse", "()V");
			minecraft_getDebugFPS = Java::Env->GetMethodID(minecraft_class, "getDebugFPS", "()I");

			minecraft_thePlayer = Java::Env->GetFieldID(minecraft_class, "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
			minecraft_theWorld = Java::Env->GetFieldID(minecraft_class, "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
			minecraft_playerController = Java::Env->GetFieldID(minecraft_class, "playerController", "Lnet/minecraft/client/multiplayer/PlayerControllerMP;");
			minecraft_renderManager = Java::Env->GetFieldID(minecraft_class, "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
			minecraft_timer = Java::Env->GetFieldID(minecraft_class, "timer", "Lnet/minecraft/util/Timer;");
			minecraft_gameSettings = Java::Env->GetFieldID(minecraft_class, "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
			minecraft_currentScreen = Java::Env->GetFieldID(minecraft_class, "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");
			minecraft_objectMouseOver = Java::Env->GetFieldID(minecraft_class, "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");
			minecraft_rightClickDelayTimer = Java::Env->GetFieldID(minecraft_class, "rightClickDelayTimer", "I");

		}

		{
			Java::AssignClass("net.minecraft.client.settings.GameSettings", gamesettings_class);
			gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);

			gamesettings_setOptionKeyBinding = Java::Env->GetMethodID(gamesettings_class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
			gamesettings_thirdPersonView = Java::Env->GetFieldID(StrayCache::gamesettings_class, "thirdPersonView", "I");
			gamesettings_fovSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "fovSetting", "F");
			gamesettings_gammaSetting = Java::Env->GetFieldID(StrayCache::gamesettings_class, "gammaSetting", "F");
			gamesettings_keyBindFullscreen = Java::Env->GetFieldID(StrayCache::gamesettings_class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
			gamesettings_keyBindSneak = Java::Env->GetFieldID(gamesettings_class, "keyBindSneak", "Lnet/minecraft/client/settings/KeyBinding;");

		}

		{
			Java::AssignClass("net.minecraft.entity.Entity", entity_class);
			entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);

			entity_getName = Java::Env->GetMethodID(entity_class, "getName", "()Ljava/lang/String;");
			entity_isSneaking = Java::Env->GetMethodID(entity_class, "isSneaking", "()Z");
			entity_setPosition = Java::Env->GetMethodID(entity_class, "setPosition", "(DDD)V");
			entity_setSneaking = Java::Env->GetMethodID(entity_class, "setSneaking", "(Z)V");
			entity_isInvisible = Java::Env->GetMethodID(entity_class, "isInvisible", "()Z");
			entity_inWater = Java::Env->GetMethodID(entity_class, "inWater", "()Z");

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
			entity_ticksExisted = Java::Env->GetFieldID(entity_class, "ticksExisted", "F");

		}


		{
			Java::AssignClass("net.minecraft.entity.EntityLivingBase", entityLivingBase_class);
			entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);

			entityLivingBase_getHealth = Java::Env->GetMethodID(entityLivingBase_class, "getHealth", "()F");
			entityLivingBase_getMaxHealth = Java::Env->GetMethodID(entityLivingBase_class, "getMaxHealth", "()F");
			entityLivingBase_canEntityBeSeen = Java::Env->GetMethodID(entityLivingBase_class, "canEntityBeSeen", "(Lnet/minecraft/entity/Entity;)Z");
			entityLivingBase_isPlayerSleeping = Java::Env->GetMethodID(entityLivingBase_class, "isPlayerSleeping", "()Z");
			entityLivingBase_hurttime = Java::Env->GetFieldID(entityLivingBase_class, "hurtTime", "I");
			entityLivingBase_moveForward = Java::Env->GetFieldID(entityLivingBase_class, "moveForward", "I");
			entityLivingBase_moveStrafe = Java::Env->GetFieldID(entityLivingBase_class, "moveStrafing", "I");
			entityLivingBase_swingItem = Java::Env->GetMethodID(entityLivingBase_class, "swingItem", "()V");
			entityLivingBase_jump = Java::Env->GetMethodID(entityLivingBase_class, "jump", "()V");
		}



		{
			Java::AssignClass("net.minecraft.entity.player.EntityPlayer", entityPlayer_class);
			entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);


			entityPlayer_inventory = Java::Env->GetFieldID(StrayCache::entityPlayer_class, "inventory", "Lnet/minecraft/entity/player/InventoryPlayer;");
		}

		Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", entityPlayerSP_class);
		entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);




		{
			Java::AssignClass("net.minecraft.client.renderer.ActiveRenderInfo", activeRenderInfo_class);
			activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);

			activeRenderInfo_PROJECTION = Java::Env->GetStaticFieldID(activeRenderInfo_class, "PROJECTION", "Ljava/nio/FloatBuffer;");
			activeRenderInfo_MODELVIEW = Java::Env->GetStaticFieldID(activeRenderInfo_class, "MODELVIEW", "Ljava/nio/FloatBuffer;");
		}


		{
			Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", renderManager_class);
			renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);


			renderManager_renderPosX = Java::Env->GetFieldID(renderManager_class, "renderPosX", "D");
			renderManager_renderPosY = Java::Env->GetFieldID(renderManager_class, "renderPosY", "D");
			renderManager_renderPosZ = Java::Env->GetFieldID(renderManager_class, "renderPosZ", "D");
			renderManager_viewerPosX = Java::Env->GetFieldID(renderManager_class, "viewerPosX", "D");
			renderManager_viewerPosY = Java::Env->GetFieldID(renderManager_class, "viewerPosY", "D");
			renderManager_viewerPosZ = Java::Env->GetFieldID(renderManager_class, "viewerPosZ", "D");
		}


		{
			Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", worldClient_class);
			worldClient_class = (jclass)Java::Env->NewGlobalRef(worldClient_class);

			worldClient_entityList = Java::Env->GetFieldID(worldClient_class, "entityList", "Ljava/util/Set;");
		}
		
		{
			Java::AssignClass("net.minecraft.world.World", world_class);
			world_class = (jclass)Java::Env->NewGlobalRef(world_class);

			world_rayTraceBlocks = Java::Env->GetMethodID(StrayCache::world_class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
			world_getChunkFromChunkCoords = Java::Env->GetMethodID(StrayCache::world_class, "getChunkFromChunkCoords", "(II)Lnet/minecraft/world/chunk/Chunk;");
			world_isAirBlock = Java::Env->GetMethodID(StrayCache::world_class, "isAirBlock", "(Lnet/minecraft/util/BlockPos;)Z");

			world_playerEntities = Java::Env->GetFieldID(StrayCache::world_class, "playerEntities", "Ljava/util/List;");
		}

		
		{
			Java::AssignClass("net.minecraft.world.chunk.Chunk", chunk_class);
			chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);

			chunk_getBlock = Java::Env->GetMethodID(StrayCache::chunk_class, "getBlock", "(III)Lnet/minecraft/block/Block;");
		}
		


		{
			Java::AssignClass("net.minecraft.util.Timer", timer_class);
			timer_class = (jclass)Java::Env->NewGlobalRef(timer_class);

			timer_timerSpeed = Java::Env->GetFieldID(StrayCache::timer_class, "timerSpeed", "F");
			timer_renderPartialTicks = Java::Env->GetFieldID(StrayCache::timer_class, "renderPartialTicks", "F");

		}

		{
			Java::AssignClass("net.minecraft.util.AxisAlignedBB", axisAlignedBB_class);
			axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);

			axisAlignedBB_minX = Java::Env->GetFieldID(axisAlignedBB_class, "minX", "D");
			axisAlignedBB_minY = Java::Env->GetFieldID(axisAlignedBB_class, "minY", "D");
			axisAlignedBB_minZ = Java::Env->GetFieldID(axisAlignedBB_class, "minZ", "D");
			axisAlignedBB_maxX = Java::Env->GetFieldID(axisAlignedBB_class, "maxX", "D");
			axisAlignedBB_maxY = Java::Env->GetFieldID(axisAlignedBB_class, "maxY", "D");
			axisAlignedBB_maxZ = Java::Env->GetFieldID(axisAlignedBB_class, "maxZ", "D");
		}

		{
			Java::AssignClass("net.minecraft.util.MovingObjectPosition", movingObjectPosition_class);
			movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);

			movingObjectPosition_hitVec = Java::Env->GetFieldID(movingObjectPosition_class, "hitVec", "Lnet/minecraft/util/Vec3;");
			movingObjectPosition_typeOfHit = Java::Env->GetFieldID(movingObjectPosition_class, "typeOfHit", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
			movingObjectPosition_blockPos = Java::Env->GetFieldID(movingObjectPosition_class, "blockPos", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
		}


		{
			Java::AssignClass("net.minecraft.util.Vec3", vec3_class);
			vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);

			vec3_xCoord = Java::Env->GetFieldID(vec3_class, "xCoord", "D");
			vec3_yCoord = Java::Env->GetFieldID(vec3_class, "yCoord", "D");
			vec3_zCoord = Java::Env->GetFieldID(vec3_class, "zCoord", "D");
		}


		{
			Java::AssignClass("net.minecraft.entity.player.InventoryPlayer", inventoryPlayer_class);
			inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);

			inventoryPlayer_getCurrentItem = Java::Env->GetMethodID(inventoryPlayer_class, "getCurrentItem", "()Lnet/minecraft/item/ItemStack;");

			inventoryPlayer_mainInv = Java::Env->GetFieldID(inventoryPlayer_class, "mainInventory", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_armorInv = Java::Env->GetFieldID(inventoryPlayer_class, "armorInventory", "[Lnet/minecraft/item/ItemStack;");
			inventoryPlayer_currentItem = Java::Env->GetFieldID(inventoryPlayer_class, "currentItem", "I");

		}

		{
			Java::AssignClass("net.minecraft.item.ItemStack", itemStack_class);
			itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);

			itemStack_getItem = Java::Env->GetMethodID(itemStack_class, "getItem", "()Lnet/minecraft/item/Item;");
			itemStack_getIdFromItem = Java::Env->GetStaticMethodID(itemStack_class, "getIdFromItem", "(Lnet/minecraft/item/Item;)I");
		}

		{
			Java::AssignClass("net.minecraft.item.Item", item_class);
			item_class = (jclass)Java::Env->NewGlobalRef(item_class);

		}

		{
			Java::AssignClass("net.minecraft.item.ItemArmor", itemArmor_Class);
			itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);

			itemArmor_getColor = Java::Env->GetMethodID(itemArmor_Class, "getColor", "(Lnet/minecraft/item/ItemStack;)I");
		}

		{
			Java::AssignClass("net.minecraft.util.BlockPos", blockPos_class);
			blockPos_x = Java::Env->GetFieldID(blockPos_class, "x", "I");
			blockPos_y = Java::Env->GetFieldID(blockPos_class, "y", "I");
			blockPos_z = Java::Env->GetFieldID(blockPos_class, "z", "I");
		}

	End:

		conllection_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/Collection"));
		conllection_toArray = Java::Env->GetMethodID(conllection_class, "toArray", "()[Ljava/lang/Object;");

		list_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/List"));
		list_toArray = Java::Env->GetMethodID(list_class, "toArray", "()[Ljava/lang/Object;");
		set_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/util/Set"));
		set_toArray = Java::Env->GetMethodID(set_class, "toArray", "()[Ljava/lang/Object;");
		
		

		floatBuffer_class = (jclass)Java::Env->NewGlobalRef(Java::Env->FindClass("java/nio/FloatBuffer"));
		floatBuffer_get = Java::Env->GetMethodID(floatBuffer_class, "get", "(I)F");
		/*set_class = (jclass)Java::Env->NewGlobalRef(set_class);
		conllection_class = (jclass)Java::Env->NewGlobalRef(conllection_class);
		list_class = (jclass)Java::Env->NewGlobalRef(list_class);
		floatBuffer_class = (jclass)Java::Env->NewGlobalRef(floatBuffer_class);
		
		activeRenderInfo_class = (jclass)Java::Env->NewGlobalRef(activeRenderInfo_class);
		gamesettings_class = (jclass)Java::Env->NewGlobalRef(gamesettings_class);
		entity_class = (jclass)Java::Env->NewGlobalRef(entity_class);
		entityLivingBase_class = (jclass)Java::Env->NewGlobalRef(entityLivingBase_class);
		entityPlayerSP_class = (jclass)Java::Env->NewGlobalRef(entityPlayerSP_class);
		entityPlayer_class = (jclass)Java::Env->NewGlobalRef(entityPlayer_class);
		chunk_class = (jclass)Java::Env->NewGlobalRef(chunk_class);
		axisAlignedBB_class = (jclass)Java::Env->NewGlobalRef(axisAlignedBB_class);
		movingObjectPosition_class = (jclass)Java::Env->NewGlobalRef(movingObjectPosition_class);
		itemStack_class = (jclass)Java::Env->NewGlobalRef(itemStack_class);
		inventoryPlayer_class = (jclass)Java::Env->NewGlobalRef(inventoryPlayer_class);
		vec3_class = (jclass)Java::Env->NewGlobalRef(vec3_class);
		itemArmor_Class = (jclass)Java::Env->NewGlobalRef(itemArmor_Class);
		item_class= (jclass)Java::Env->NewGlobalRef(item_class);
		renderManager_class = (jclass)Java::Env->NewGlobalRef(renderManager_class);*/
		initialized = true;
	}

	static void DeleteRefs() {
		Java::Env->DeleteGlobalRef(set_class);
		Java::Env->DeleteGlobalRef(list_class);
		Java::Env->DeleteGlobalRef(floatBuffer_class);
		Java::Env->DeleteGlobalRef(minecraft_class);
		Java::Env->DeleteGlobalRef(activeRenderInfo_class);
		Java::Env->DeleteGlobalRef(gamesettings_class);
		Java::Env->DeleteGlobalRef(entity_class);
		Java::Env->DeleteGlobalRef(entityLivingBase_class);
		Java::Env->DeleteGlobalRef(entityPlayerSP_class);
		Java::Env->DeleteGlobalRef(entityPlayer_class);
		Java::Env->DeleteGlobalRef(chunk_class);
		Java::Env->DeleteGlobalRef(axisAlignedBB_class);
		Java::Env->DeleteGlobalRef(movingObjectPosition_class);
		Java::Env->DeleteGlobalRef(itemStack_class);
		Java::Env->DeleteGlobalRef(inventoryPlayer_class);
		Java::Env->DeleteGlobalRef(vec3_class);
		Java::Env->DeleteGlobalRef(itemArmor_Class);
		Java::Env->DeleteGlobalRef(item_class);
		Java::Env->DeleteGlobalRef(renderManager_class);

	}
};