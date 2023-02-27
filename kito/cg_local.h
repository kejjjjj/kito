#pragma once

#ifndef cglocal
#define cglocal
#include "pch.h"

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define	MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// water physics in these contents
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define	MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define	MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

#define	PITCH					0		// up / down
#define	YAW						1		// left / right
#define	ROLL					2		// fall over

constexpr auto CMD_MASK = 0x3F;

enum pmflags_t
{
	PMF_NONE = 0x0,
	PMF_PRONE = 0x1,
	PMF_DUCKED = 0x2,
	PMF_MANTLE = 0x4,
	PMF_LADDER = 0x8,
	PMF_SIGHT_AIMING = 0x10,
	PMF_BACKWARDS_RUN = 0x20,
	PMF_LADDER_DOWN = 0x30,
	PMF_WALKING = 0x40,
	PMF_TIME_LAND = 0x80,
	PMF_TIME_KNOCKBACK = 0x100,
	PMF_PRONEMOVE_OVERRIDDEN = 0x200,
	PMF_RESPAWNED = 0x400,
	PMF_FROZEN = 0x800,
	PMF_PRONE_BLOCKED = 0x1000,
	PMF_LADDER_FALL = 0x2000,
	PMF_JUMPING = 0x4000,
	PMF_SPRINTING = 0x8000,
	PMF_SHELLSHOCKED = 0x10000,
	PMF_MELEE_CHARGE = 0x20000,
	PMF_NO_SPRINT = 0x40000,
	PMF_NO_JUMP = 0x80000,
	PMF_VEHICLE_ATTACHED = 0x100000,
};


struct GfxWindowTarget
{
	HWND__* hwnd;
	void* swapChain;
	int width;
	int height;
};

struct __declspec(align(8)) DxGlobals
{
	IDirect3D9* d3d9;
	IDirect3DDevice9* device;
	unsigned int adapterIndex;
	bool adapterNativeIsValid;
	int adapterNativeWidth;
	int adapterNativeHeight;
	int adapterFullscreenWidth;
	int adapterFullscreenHeight;
	int depthStencilFormat;
	unsigned int displayModeCount;
	_D3DDISPLAYMODE displayModes[256];
	const char* resolutionNameTable[257];
	const char* refreshRateNameTable[257];
	char modeText[5120];
	IDirect3DQuery9* fencePool[8];
	unsigned int nextFence;
	int gpuSync;
	int multiSampleType;
	unsigned int multiSampleQuality;
	int sunSpriteSamples;
	IDirect3DSurface9* singleSampleDepthStencilSurface;
	bool deviceLost;
	bool inScene;
	int targetWindowIndex;
	int windowCount;
	GfxWindowTarget windows[1];
	int flushGpuQueryCount;
	IDirect3DQuery9* flushGpuQuery;
	unsigned __int64 gpuSyncDelay;
	unsigned __int64 gpuSyncStart;
	unsigned __int64 gpuSyncEnd;
	bool flushGpuQueryIssued;
	int linearNonMippedMinFilter;
	int linearNonMippedMagFilter;
	int linearMippedMinFilter;
	int linearMippedMagFilter;
	int anisotropicMinFilter;
	int anisotropicMagFilter;
	int linearMippedAnisotropy;
	int anisotropyFor2x;
	int anisotropyFor4x;
	int mipFilterMode;
	unsigned int mipBias;
	IDirect3DQuery9* swapFence;
};


namespace cmdEnums
{
	enum Buttons
	{
		fire = 1,
		melee = 4,
		activate = 8,
		reload = 16,
		lean_left = 64,
		lean_right = 128,
		prone = 256,
		crouch = 512,
		jump = 1024,
		ads_toggle_on = 2048,
		crouch_hold = 4608,
		prone_hold = 4352,
		steady_aim = 8192,
		sprint = 8194,
		frag = 16384,
		special_grenade = 32768,
		ads_toggle_off = 524288,
		ads_hold = 526336,
		no_input = 1048576 //such as menu open or chat is open
	};

	enum Move : char
	{
		noInput = 0,
		forward = 127,
		back = -127
	};
	enum Strafe : char
	{
		left = -127,
		right = 127
	};
};

//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//
struct usercmd_s
{
	int serverTime; //0x004
	int buttons;//0x008
	int angles[3]; //0x00C 
	char weapon;
	char offHandIndex;
	char forwardmove; 
	char rightmove; 
	char pad[0x20];
	//float meleeChargeYaw;
	//char meleeChargeDist;
	//char selectedLocation[2];
};
static_assert(sizeof(usercmd_s) == 0x38);

struct coordinates
{
	float origin[3];
};
struct viewangles
{
	float angles[3];
};
enum OffhandSecondaryClass
{
	PLAYER_OFFHAND_SECONDARY_SMOKE = 0x0,
	PLAYER_OFFHAND_SECONDARY_FLASH = 0x1,
	PLAYER_OFFHAND_SECONDARIES_TOTAL = 0x2,
};

enum ViewLockTypes
{
	PLAYERVIEWLOCK_NONE = 0x0,
	PLAYERVIEWLOCK_FULL = 0x1,
	PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
	PLAYERVIEWLOCKCOUNT = 0x3,
};

enum ActionSlotType
{
	ACTIONSLOTTYPE_DONOTHING = 0x0,
	ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
	ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
	ACTIONSLOTTYPE_NIGHTVISION = 0x3,
	ACTIONSLOTTYPECOUNT = 0x4,
};

struct SprintState
{
	int sprintButtonUpRequired;
	int sprintDelay;
	int lastSprintStart;
	int lastSprintEnd;
	int sprintStartMaxLength;
};

/* 827 */
struct MantleState
{
	float yaw;
	int timer;
	int transIndex;
	int flags;
};
struct MantleResults
{
	float dir[3];
	float startPos[3];
	float ledgePos[3];
	float endPos[3];
	int flags;
};

struct ActionSlotParam_SpecifyWeapon
{
	unsigned int index;
};

struct ActionSlotParam
{
	ActionSlotParam_SpecifyWeapon specifyWeapon;
};

enum objectiveState_t
{
	OBJST_EMPTY = 0x0,
	OBJST_ACTIVE = 0x1,
	OBJST_INVISIBLE = 0x2,
	OBJST_DONE = 0x3,
	OBJST_CURRENT = 0x4,
	OBJST_FAILED = 0x5,
	OBJST_NUMSTATES = 0x6,
};
struct objective_t
{
	objectiveState_t state;
	float origin[3];
	int entNum;
	int teamNum;
	int icon;
};
struct $C96EA5EC2ACBB9C0BF22693F316ACC67
{
	char r;
	char g;
	char b;
	char a;
};

union hudelem_color_t
{
	$C96EA5EC2ACBB9C0BF22693F316ACC67 __s0;
	int rgba;
};
enum he_type_t
{
	HE_TYPE_FREE = 0x0,
	HE_TYPE_TEXT = 0x1,
	HE_TYPE_VALUE = 0x2,
	HE_TYPE_PLAYERNAME = 0x3,
	HE_TYPE_MAPNAME = 0x4,
	HE_TYPE_GAMETYPE = 0x5,
	HE_TYPE_MATERIAL = 0x6,
	HE_TYPE_TIMER_DOWN = 0x7,
	HE_TYPE_TIMER_UP = 0x8,
	HE_TYPE_TENTHS_TIMER_DOWN = 0x9,
	HE_TYPE_TENTHS_TIMER_UP = 0xA,
	HE_TYPE_CLOCK_DOWN = 0xB,
	HE_TYPE_CLOCK_UP = 0xC,
	HE_TYPE_WAYPOINT = 0xD,
	HE_TYPE_COUNT = 0xE,
};
struct hudelem_s
{
	he_type_t type;
	float x;
	float y;
	float z;
	int targetEntNum;
	float fontScale;
	int font;
	int alignOrg;
	int alignScreen;
	hudelem_color_t color;
	hudelem_color_t fromColor;
	int fadeStartTime;
	int fadeTime;
	int label;
	int width;
	int height;
	int materialIndex;
	int offscreenMaterialIdx;
	int fromWidth;
	int fromHeight;
	int scaleStartTime;
	int scaleTime;
	float fromX;
	float fromY;
	int fromAlignOrg;
	int fromAlignScreen;
	int moveStartTime;
	int moveTime;
	int time;
	int duration;
	float value;
	int text;
	float sort;
	hudelem_color_t glowColor;
	int fxBirthTime;
	int fxLetterTime;
	int fxDecayStartTime;
	int fxDecayDuration;
	int soundID;
	int flags;
};
struct $15067B6A14D88D7E1E730369692C3A81
{
	hudelem_s current[31];
	hudelem_s archival[31];
};
enum weaponstate_t
{
	WEAPON_READY = 0x0,
	WEAPON_RAISING = 0x1,
	WEAPON_RAISING_ALTSWITCH = 0x2,
	WEAPON_DROPPING = 0x3,
	WEAPON_DROPPING_QUICK = 0x4,
	WEAPON_FIRING = 0x5,
	WEAPON_RECHAMBERING = 0x6,
	WEAPON_RELOADING = 0x7,
	WEAPON_RELOADING_INTERUPT = 0x8,
	WEAPON_RELOAD_START = 0x9,
	WEAPON_RELOAD_START_INTERUPT = 0xA,
	WEAPON_RELOAD_END = 0xB,
	WEAPON_MELEE_INIT = 0xC,
	WEAPON_MELEE_FIRE = 0xD,
	WEAPON_MELEE_END = 0xE,
	WEAPON_OFFHAND_INIT = 0xF,
	WEAPON_OFFHAND_PREPARE = 0x10,
	WEAPON_OFFHAND_HOLD = 0x11,
	WEAPON_OFFHAND_START = 0x12,
	WEAPON_OFFHAND = 0x13,
	WEAPON_OFFHAND_END = 0x14,
	WEAPON_DETONATING = 0x15,
	WEAPON_SPRINT_RAISE = 0x16,
	WEAPON_SPRINT_LOOP = 0x17,
	WEAPON_SPRINT_DROP = 0x18,
	WEAPON_NIGHTVISION_WEAR = 0x19,
	WEAPON_NIGHTVISION_REMOVE = 0x1A,
	WEAPONSTATES_NUM = 0x1B,
};

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur
struct playerState_s
{
	int commandTime;
	int pm_type;
	int bobCycle;
	int pm_flags;
	int weapFlags;
	int otherFlags;
	int pm_time;
	float origin[3];
	float velocity[3];
	float oldVelocity[2];
	int weaponTime;
	int weaponDelay;
	int grenadeTimeLeft;
	int throwBackGrenadeOwner;
	int throwBackGrenadeTimeLeft;
	int weaponRestrictKickTime;
	int foliageSoundTime;
	int gravity;
	float leanf;
	int speed;
	float delta_angles[3];
	int groundEntityNum;
	float vLadderVec[3];
	int jumpTime;
	float jumpOriginZ;
	int movementDir;
	int eFlags;
	int eventSequence;
	int events[4];
	unsigned int eventParms[4];
	int oldEventSequence;
	int clientNum;
	int offHandIndex;
	OffhandSecondaryClass offhandSecondary;
	unsigned int weapon;
	int weaponstate;
	unsigned int weaponShotCount;
	float fWeaponPosFrac;
	int adsDelayTime;
	int spreadOverride;
	int spreadOverrideState;
	int viewmodelIndex;
	float viewangles[3];
	int viewHeightTarget;
	float viewHeightCurrent;
	int viewHeightLerpTime;
	int viewHeightLerpTarget;
	int viewHeightLerpDown;
	float viewAngleClampBase[2];
	float viewAngleClampRange[2];
	int damageEvent;
	int damageYaw;
	int damagePitch;
	int damageCount;
	int ammo[128];
	int ammoclip[128];
	unsigned int weaponold[4];
	unsigned int weapons[4];
	unsigned int weaponchamber[3];
	int stats[5];
	float proneDirection;
	float proneDirectionPitch;
	float proneTorsoPitch;
	ViewLockTypes viewlocked;
	int viewlocked_entNum;
	int cursorHint;
	int cursorHintString;
	int cursorHintEntIndex;
	int iCompassPlayerInfo;
	int radarEnabled;
	int locationSelectionInfo;
	int pad00[5];
	SprintState sprintState;
	float fTorsoPitch;
	float fWaistPitch;
	float holdBreathScale;
	int holdBreathTimer;
	float moveSpeedScaleMultiplier;
	MantleState mantleState;
	float meleeChargeYaw;
	int meleeChargeDist;
	int meleeChargeTime;
	int perks;
	ActionSlotType actionSlotType[4];
	ActionSlotParam actionSlotParam[4];
	int entityEventSequence;
	char _pad[16];
	int weapAnim;
	float aimSpreadScale;
	int shellshockIndex;
	int shellshockTime;
	int shellshockDuration;
	float dofNearStart;
	float dofNearEnd;
	float dofFarStart;
	float dofFarEnd;
	float dofNearBlur;
	float dofFarBlur;
	float dofViewmodelStart;
	float dofViewmodelEnd;
	int hudElemLastAssignedSoundID;
	objective_t objective[16];
	char weaponmodels[128];
	int deltaTime;
	int killCamEntity;
	$15067B6A14D88D7E1E730369692C3A81 hud;
};



struct playerState_t_origin
{
	float origin[3];
	float velocity[3];
};
struct velocity
{
	float velocity[3];
};
struct recorder_cmds
{
	UINT frame;
	int serverTime;
	int buttons;
	int angles[3];
	char forwardmove;
	char rightmove;
	float fps;
	float origin[3];
	float velocity[3];
	char weapon;
};
struct recorder_once
{
	float startpos[3];
	float endpos[3];
};
struct CInput
{
	usercmd_s cmds[CMD_MASK + 1]; // 
	int cmdNumber;

	usercmd_s* GetUserCmd(int cmdNum)
	{
		return &cmds[cmdNum & CMD_MASK];
	}

};
enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
};

struct __declspec(align(4)) trace_t
{
	float fraction;
	float normal[3];
	int surfaceFlags;
	int contents;
	const char* material;
	TraceHitType hitType;
	unsigned __int16 hitId;
	unsigned __int16 modelIndex;
	unsigned __int16 partName;
	unsigned __int16 partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
};
struct __declspec(align(4)) pmove_t
{
	playerState_s* ps;
	usercmd_s cmd;
	usercmd_s oldcmd;
	int tracemask;
	int numtouch;
	int touchents[32];
	float mins[3];
	float maxs[3];
	float xyspeed;
	int viewChangeTime;
	float viewChange;
	char handler;
};
struct pml_t
{
	float forward[3];
	float right[3];
	float up[3];
	float frametime;
	int msec;
	int walking;
	int groundPlane;
	trace_t groundTrace;
	float impactSpeed;
	float previous_origin[3];
	float previous_velocity[3];
};
struct pmoveHandler_t
{
	void(__cdecl* trace)(trace_t*, const float*, const float*, const float*, const float*, int, int);
	void(__cdecl* playerEvent)(int, int);
};

class Movement
{
public:
	bool forward; //0x0000
	char pad_0001[3]; //0x0001
	char N00000077[2]; //0x0004
	char pad_0006[13]; //0x0006
	int8_t N00000079; //0x0013
	bool back; //0x0014
	char pad_0015[59]; //0x0015
	bool left; //0x0050
	char pad_0051[19]; //0x0051
	bool right; //0x0064
	char pad_0065[39]; //0x0065
	bool adshold; //0x008C
	char pad_008D[19]; //0x008D
	bool jump; //0x00A0
	char pad_00A1[19]; //0x00A1
	bool lowerstance; //0x00B4
	char pad_00B5[19]; //0x00B5
	bool raisestance; //0x00C8
	char pad_00C9[39]; //0x00C9
	bool attack; //0x00F0
	char pad_00F1[19]; //0x00F1
	bool sprint; //0x0104
	char pad_0105[19]; //0x0105
	bool nade; //0x0118
	char pad_0119[39]; //0x0119
	bool knife; //0x0140
	char pad_0141[79]; //0x0141
	bool leanleft; //0x0190
	char pad_0191[19]; //0x0191
	bool leanright; //0x01A4
	char pad_01A5[287]; //0x01A5

}; //Size: 0x02C4
static_assert(sizeof(Movement) == 0x2C4);

struct GfxDepthOfField
{
	float viewModelStart;
	float viewModelEnd;
	float nearStart;
	float nearEnd;
	float farStart;
	float farEnd;
	float nearBlur;
	float farBlur;
};

struct GfxFilm
{
	bool enabled;
	float brightness;
	float contrast;
	float desaturation;
	bool invert;
	float tintDark[3];
	float tintLight[3];
};

struct GfxGlow
{
	bool enabled;
	float bloomCutoff;
	float bloomDesaturation;
	float bloomIntensity;
	float radius;
};


struct GfxSunShadowBoundingPoly
{
	float snapDelta[2];
	int pointCount;
	float points[9][2];
	int pointIsNear[9];
};
enum MapType
{
	MAPTYPE_NONE = 0x0,
	MAPTYPE_INVALID1 = 0x1,
	MAPTYPE_INVALID2 = 0x2,
	MAPTYPE_2D = 0x3,
	MAPTYPE_3D = 0x4,
	MAPTYPE_CUBE = 0x5,
	MAPTYPE_COUNT = 0x6,
};

struct Picmip
{
	char platform[2];
};

struct CardMemory
{
	int platform[2];
};

struct GfxImageLoadDef
{
	char levelCount;
	char flags;
	__int16 dimensions[3];
	int format;
	int resourceSize;
	char data[1];
};

union GfxTexture
{
	/*IDirect3DBaseTexture9 *basemap;
	IDirect3DTexture9 *map;
	IDirect3DVolumeTexture9 *volmap;
	IDirect3DCubeTexture9 *cubemap;*/
	GfxImageLoadDef* loadDef;
	void* data;
};

struct GfxImage
{
	MapType mapType;
	GfxTexture texture;
	Picmip picmip;
	bool noPicmip;
	char semantic;
	char track;
	CardMemory cardMemory;
	unsigned __int16 width;
	unsigned __int16 height;
	unsigned __int16 depth;
	char category;
	bool delayLoadPixels;
	const char* name;
};
struct __declspec(align(4)) GfxLightImage
{
	GfxImage* image;
	char samplerState;
};

struct GfxLightDef
{
	const char* name;
	GfxLightImage attenuation;
	int lmapLookupStart;
};

struct GfxLight
{
	char type;
	char canUseShadowMap;
	char unused[2];
	float color[3];
	float dir[3];
	float origin[3];
	float radius;
	float cosHalfFovOuter;
	float cosHalfFovInner;
	int exponent;
	unsigned int spotShadowIndex;
	GfxLightDef* def;
};
struct GfxViewport
{
	int x;
	int y;
	int width;
	int height;
};
struct __declspec(align(4)) WinMouseVars_t
{
	int oldButtonState;
	tagPOINT oldPos;
	bool mouseActive;
	bool mouseInitialized;
};
struct cmd_function_s
{
	cmd_function_s* next;
	const char* name;
	const char* args;			//autoCompleteDir;
	const char* description;	// autoCompleteExt
	void(__cdecl* function)();
};

struct refdef_s
{
	unsigned int width;
	unsigned int height;
	float tanHalfFovX;
	float tanHalfFovY;
	float vieworg[3];
	float viewaxis[3][3];
	float viewOffset[3];
	int time;
	float zNear;
	float blurRadius;
	GfxDepthOfField dof;
	GfxFilm film;
	GfxGlow glow;
	GfxLight primaryLights[255];
	GfxViewport scissorViewport;
	bool useScissorViewport;
	int localClientNum;
};



enum weapType_t
{
	WEAPTYPE_BULLET = 0x0,
	WEAPTYPE_GRENADE = 0x1,
	WEAPTYPE_PROJECTILE = 0x2,
	WEAPTYPE_BINOCULARS = 0x3,
	WEAPTYPE_NUM = 0x4,
};

enum weapClass_t
{
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_MG = 0x1,
	WEAPCLASS_SMG = 0x2,
	WEAPCLASS_SPREAD = 0x3,
	WEAPCLASS_PISTOL = 0x4,
	WEAPCLASS_GRENADE = 0x5,
	WEAPCLASS_ROCKETLAUNCHER = 0x6,
	WEAPCLASS_TURRET = 0x7,
	WEAPCLASS_NON_PLAYER = 0x8,
	WEAPCLASS_ITEM = 0x9,
	WEAPCLASS_NUM = 0xA,
};

enum PenetrateType
{
	PENETRATE_TYPE_NONE = 0x0,
	PENETRATE_TYPE_SMALL = 0x1,
	PENETRATE_TYPE_MEDIUM = 0x2,
	PENETRATE_TYPE_LARGE = 0x3,
	PENETRATE_TYPE_COUNT = 0x4,
};

enum ImpactType
{
	IMPACT_TYPE_NONE = 0x0,
	IMPACT_TYPE_BULLET_SMALL = 0x1,
	IMPACT_TYPE_BULLET_LARGE = 0x2,
	IMPACT_TYPE_BULLET_AP = 0x3,
	IMPACT_TYPE_SHOTGUN = 0x4,
	IMPACT_TYPE_GRENADE_BOUNCE = 0x5,
	IMPACT_TYPE_GRENADE_EXPLODE = 0x6,
	IMPACT_TYPE_ROCKET_EXPLODE = 0x7,
	IMPACT_TYPE_PROJECTILE_DUD = 0x8,
	IMPACT_TYPE_COUNT = 0x9,
};

enum weapInventoryType_t
{
	WEAPINVENTORY_PRIMARY = 0x0,
	WEAPINVENTORY_OFFHAND = 0x1,
	WEAPINVENTORY_ITEM = 0x2,
	WEAPINVENTORY_ALTMODE = 0x3,
	WEAPINVENTORYCOUNT = 0x4,
};

enum weapFireType_t
{
	WEAPON_FIRETYPE_FULLAUTO = 0x0,
	WEAPON_FIRETYPE_SINGLESHOT = 0x1,
	WEAPON_FIRETYPE_BURSTFIRE2 = 0x2,
	WEAPON_FIRETYPE_BURSTFIRE3 = 0x3,
	WEAPON_FIRETYPE_BURSTFIRE4 = 0x4,
	WEAPON_FIRETYPECOUNT = 0x5,
};

enum OffhandClass
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_COUNT = 0x4,
};

enum weapStance_t
{
	WEAPSTANCE_STAND = 0x0,
	WEAPSTANCE_DUCK = 0x1,
	WEAPSTANCE_PRONE = 0x2,
	WEAPSTANCE_NUM = 0x3,
};

struct snd_alias_list_t
{
	/*const char *aliasName;
	snd_alias_t *head;
	int count;*/
};

enum activeReticleType_t
{
	VEH_ACTIVE_RETICLE_NONE = 0x0,
	VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
	VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,
	VEH_ACTIVE_RETICLE_COUNT = 0x3,
};

enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};

enum ammoCounterClipType_t
{
	AMMO_COUNTER_CLIP_NONE = 0x0,
	AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
	AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
	AMMO_COUNTER_CLIP_ROCKET = 0x4,
	AMMO_COUNTER_CLIP_BELTFED = 0x5,
	AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,
	AMMO_COUNTER_CLIP_COUNT = 0x7,
};

enum weapOverlayReticle_t
{
	WEAPOVERLAYRETICLE_NONE = 0x0,
	WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,
	WEAPOVERLAYRETICLE_NUM = 0x2,
};

enum WeapOverlayInteface_t
{
	WEAPOVERLAYINTERFACE_NONE = 0x0,
	WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
	WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,
	WEAPOVERLAYINTERFACECOUNT = 0x3,
};

enum weapProjExposion_t
{
	WEAPPROJEXP_GRENADE = 0x0,
	WEAPPROJEXP_ROCKET = 0x1,
	WEAPPROJEXP_FLASHBANG = 0x2,
	WEAPPROJEXP_NONE = 0x3,
	WEAPPROJEXP_DUD = 0x4,
	WEAPPROJEXP_SMOKE = 0x5,
	WEAPPROJEXP_HEAVY = 0x6,
	WEAPPROJEXP_NUM = 0x7,
};

enum WeapStickinessType
{
	WEAPSTICKINESS_NONE = 0x0,
	WEAPSTICKINESS_ALL = 0x1,
	WEAPSTICKINESS_GROUND = 0x2,
	WEAPSTICKINESS_GROUND_WITH_YAW = 0x3,
	WEAPSTICKINESS_COUNT = 0x4,
};

enum guidedMissileType_t
{
	MISSILE_GUIDANCE_NONE = 0x0,
	MISSILE_GUIDANCE_SIDEWINDER = 0x1,
	MISSILE_GUIDANCE_HELLFIRE = 0x2,
	MISSILE_GUIDANCE_JAVELIN = 0x3,
	MISSILE_GUIDANCE_COUNT = 0x4,
};

struct DObjAnimMat
{
	float quat[4];
	float trans[3];
	float transWeight;
};
struct XSurfaceVertexInfo
{
	short vertCount[4];
	unsigned short* vertsBlend;
};
// fucking namespaces
union PackedUnitVec
{
	unsigned int packed;
	char array[4];
};

// fucking namespaces
union GfxColor
{
	unsigned int packed;
	char array[4];
};
// fucking namespaces
struct GfxWorldVertex
{
	float xyz[3];
	float binormalSign;
	GfxColor color;
	float texCoord[2];
	float lmapCoord[2];
	PackedUnitVec normal;
	PackedUnitVec tangent;
};
union PackedTexCoords
{
	unsigned int packed;
};
struct GfxPackedVertex
{
	float xyz[3];
	float binormalSign;
	GfxColor color;
	PackedTexCoords texCoord;
	PackedUnitVec normal;
	PackedUnitVec tangent;
};
struct XSurfaceCollisionAabb
{
	unsigned short mins[3];
	unsigned short maxs[3];
};

struct XSurfaceCollisionNode
{
	XSurfaceCollisionAabb aabb;
	unsigned short childBeginIndex;
	unsigned short childCount;
};

struct XSurfaceCollisionLeaf
{
	unsigned short triangleBeginIndex;
};

struct XSurfaceCollisionTree
{
	float trans[3];
	float scale[3];
	unsigned int nodeCount;
	XSurfaceCollisionNode* nodes;
	unsigned int leafCount;
	XSurfaceCollisionLeaf* leafs;
};

struct XRigidVertList
{
	unsigned short boneOffset;
	unsigned short vertCount;
	unsigned short triOffset;
	unsigned short triCount;
	XSurfaceCollisionTree* collisionTree;
};
struct XSurface
{
	char tileMode;
	bool deformed;
	unsigned __int16 vertCount;
	unsigned __int16 triCount;
	char zoneHandle;
	unsigned __int16 baseTriIndex;
	unsigned __int16 baseVertIndex;
	unsigned __int16* triIndices;
	XSurfaceVertexInfo vertInfo;
	GfxPackedVertex* verts0;
	unsigned int vertListCount;
	XRigidVertList* vertList;
	int partBits[4];
};
struct GfxDrawSurfFields
{
	unsigned __int64 objectId : 16;
	unsigned __int64 reflectionProbeIndex : 8;
	unsigned __int64 customIndex : 5;
	unsigned __int64 materialSortedIndex : 11;
	unsigned __int64 prepass : 2;
	unsigned __int64 primaryLightIndex : 8;
	unsigned __int64 surfType : 4;
	unsigned __int64 primarySortKey : 6;
	unsigned __int64 unused : 4;
};

union GfxDrawSurf
{
	GfxDrawSurfFields fields;
	unsigned long long packed;
};

#pragma pack(push, 4)
struct MaterialInfo
{
	const char* name;
	char gameFlags;
	char sortKey;
	char textureAtlasRowCount;
	char textureAtlasColumnCount;
	GfxDrawSurf drawSurf;
	unsigned int surfaceTypeBits;
	unsigned __int16 hashIndex;
};
#pragma pack(pop)

/* MaterialTechniqueSet->worldVertFormat */
enum MaterialWorldVertexFormat : char
{
	MTL_WORLDVERT_TEX_1_NRM_1 = 0x0,
	MTL_WORLDVERT_TEX_2_NRM_1 = 0x1,
	MTL_WORLDVERT_TEX_2_NRM_2 = 0x2,
	MTL_WORLDVERT_TEX_3_NRM_1 = 0x3,
	MTL_WORLDVERT_TEX_3_NRM_2 = 0x4,
	MTL_WORLDVERT_TEX_3_NRM_3 = 0x5,
	MTL_WORLDVERT_TEX_4_NRM_1 = 0x6,
	MTL_WORLDVERT_TEX_4_NRM_2 = 0x7,
	MTL_WORLDVERT_TEX_4_NRM_3 = 0x8,
	MTL_WORLDVERT_TEX_5_NRM_1 = 0x9,
	MTL_WORLDVERT_TEX_5_NRM_2 = 0xA,
	MTL_WORLDVERT_TEX_5_NRM_3 = 0xB,
};
struct GfxVertexShaderLoadDef
{
	unsigned int* program;
	unsigned __int16 programSize;
	unsigned __int16 loadForRenderer;
};

struct MaterialVertexShaderProgram
{
	void* vs;
	GfxVertexShaderLoadDef loadDef;
};

struct MaterialVertexShader
{
	const char* name;
	MaterialVertexShaderProgram prog;
};
struct MaterialStreamRouting
{
	char source;
	char dest;
};

struct MaterialVertexStreamRouting
{
	MaterialStreamRouting data[16];
	void* decl[16];
};
struct GfxPixelShaderLoadDef
{
	unsigned int* program;
	unsigned __int16 programSize;
	unsigned __int16 loadForRenderer;
};
struct MaterialVertexDeclaration
{
	char streamCount;
	bool hasOptionalSource;
	bool isLoaded;
	MaterialVertexStreamRouting routing;
};
struct MaterialPixelShaderProgram
{
	void* ps;
	GfxPixelShaderLoadDef loadDef;
};
struct MaterialPixelShader
{
	const char* name;
	MaterialPixelShaderProgram prog;
};
struct MaterialArgumentCodeConst
{
	unsigned __int16 index;
	char firstRow;
	char rowCount;
};

union MaterialArgumentDef
{
	const float* literalConst;
	MaterialArgumentCodeConst codeConst;
	unsigned int codeSampler;
	unsigned int nameHash;
};

/* MaterialShaderArgument->type */
#define MTL_ARG_MATERIAL_VERTEX_CONST	0x0
#define MTL_ARG_LITERAL_VERTEX_CONST	0x1
#define MTL_ARG_MATERIAL_PIXEL_SAMPLER	0x2
#define MTL_ARG_CODE_VERTEX_CONST	    0x3
#define MTL_ARG_CODE_PIXEL_SAMPLER	    0x4
#define MTL_ARG_CODE_PIXEL_CONST	    0x5
#define MTL_ARG_MATERIAL_PIXEL_CONST	0x6
#define MTL_ARG_LITERAL_PIXEL_CONST	    0x7

struct MaterialShaderArgument
{
	unsigned __int16 type;
	unsigned __int16 dest;
	MaterialArgumentDef u;
};

#pragma pack(push, 4)
struct MaterialPass
{
	MaterialVertexDeclaration* vertexDecl;
	MaterialVertexShader* vertexShader;
	MaterialPixelShader* pixelShader;
	char perPrimArgCount;
	char perObjArgCount;
	char stableArgCount;
	char customSamplerFlags;
	MaterialShaderArgument* args;
};
#pragma pack(pop)

struct MaterialTechnique
{
	const char* name;
	unsigned __int16 flags;
	unsigned __int16 passCount;
	MaterialPass passArray[1];	// count = passCount
};


struct complex_s
{
	float real;
	float imag;
};
struct WaterWritable
{
	float floatTime;
};
struct water_t
{
	WaterWritable writable;
	complex_s* H0;
	float* wTerm;
	int M;
	int N;
	float Lx;
	float Lz;
	float gravity;
	float windvel;
	float winddir[2];
	float amplitude;
	float codeConstant[4];
	GfxImage* image;
};
union MaterialTextureDefInfo
{
	GfxImage* image;	// MaterialTextureDef->semantic != TS_WATER_MAP
	water_t* water;		// MaterialTextureDef->semantic == TS_WATER_MAP
};
struct MaterialTextureDef
{
	unsigned int nameHash;
	char nameStart;
	char nameEnd;
	char samplerState;
	char semantic;
	MaterialTextureDefInfo u;
};
struct MaterialConstantDef
{
	int nameHash;
	char name[12];
	vec4_t literal;
};
struct GfxStateBits
{
	unsigned int loadBits[2];
};
/*struct MaterialTechniqueSet // org
{
	char *name;
	MaterialWorldVertexFormat worldVertFormat;
	MaterialTechnique *techniques[34];
};*/

struct MaterialTechniqueSet
{
	char* name;
	MaterialWorldVertexFormat worldVertFormat;
	bool hasBeenUploaded;
	char unused[1];
	MaterialTechniqueSet* remappedTechniqueSet;
	MaterialTechnique* techniques[34];
};

struct Material
{
	MaterialInfo info;
	char stateBitsEntry[34];
	char textureCount;
	char constantCount;
	char stateBitsCount;
	char stateFlags;
	char cameraRegion;
	MaterialTechniqueSet* techniqueSet;
	MaterialTextureDef* textureTable;
	MaterialConstantDef* constantTable;
	GfxStateBits* stateBitsTable;
};
struct XModelLodInfo
{
	float dist;
	unsigned __int16 numsurfs;
	unsigned __int16 surfIndex;
	int partBits[4];
	char lod;
	char smcIndexPlusOne;
	char smcAllocBits;
	char unused;
};
struct XModelCollTri_s
{
	float plane[4];
	float svec[4];
	float tvec[4];
};

struct XModelCollSurf_s
{
	XModelCollTri_s* collTris;
	int numCollTris;
	float mins[3];
	float maxs[3];
	int boneIdx;
	int contents;
	int surfFlags;
};
struct XBoneInfo
{
	float bounds[2][3];
	float offset[3];
	float radiusSquared;
};
struct XModelHighMipBounds
{
	float mins[3];
	float maxs[3];
};

struct XModelStreamInfo
{
	XModelHighMipBounds* highMipBounds;
};
#pragma pack(push, 4)
struct PhysPreset
{
	const char* name;
	int type;
	float mass;
	float bounce;
	float friction;
	float bulletForceScale;
	float explosiveForceScale;
	const char* sndAliasPrefix;
	float piecesSpreadFraction;
	float piecesUpwardVelocity;
	char tempDefaultToCylinder;
};
#pragma pack(pop)
struct cplane_s
{
	float normal[3];
	float dist;
	char type;
	char signbits;
	char pad[2];
};

#pragma pack(push, 2)
struct cbrushside_t
{
	cplane_s* plane;
	unsigned int materialNum;
	__int16 firstAdjacentSideOffset;
	char edgeCount;
};
#pragma pack(pop)

struct BrushWrapper
{
	float mins[3];
	int contents;
	float maxs[3];
	unsigned int numsides;
	cbrushside_t* sides;
	__int16 axialMaterialNum[2][3];
	char* baseAdjacentSide;
	__int16 firstAdjacentSideOffsets[2][3];
	char edgeCount[2][3];
	int totalEdgeCount;
	cplane_s* planes;
};
struct PhysMass
{
	float centerOfMass[3];
	float momentsOfInertia[3];
	float productsOfInertia[3];
};

struct PhysGeomInfo
{
	BrushWrapper* brush;
	int type;
	float orientation[3][3];
	float offset[3];
	float halfLengths[3];
};

struct PhysGeomList
{
	unsigned int count;
	PhysGeomInfo* geoms;
	PhysMass mass;
};
struct XModel
{
	const char* name;
	char numBones;
	char numRootBones;
	unsigned char numsurfs;
	char lodRampType;
	unsigned __int16* boneNames;
	char* parentList;
	__int16* quats;
	float* trans;
	char* partClassification;
	DObjAnimMat* baseMat;
	XSurface* surfs;
	Material** materialHandles;
	XModelLodInfo lodInfo[4];
	XModelCollSurf_s* collSurfs;
	int numCollSurfs;
	int contents;
	XBoneInfo* boneInfo;
	float radius;
	float mins[3];
	float maxs[3];
	__int16 numLods;
	__int16 collLod;
	XModelStreamInfo streamInfo;
	int memUsage;
	char flags;
	bool bad;
	PhysPreset* physPreset;
	PhysGeomList* physGeoms;
};
struct FxEffectDef_Placeholder
{
	const char* name;
};
struct GfxPlacement
{
	float quat[4];
	float origin[3];
};
struct DynEntityDef
{
	int type;
	GfxPlacement pose;
	XModel* xModel;
	unsigned __int16 brushModel;
	unsigned __int16 physicsBrushModel;
	FxEffectDef_Placeholder* destroyFx;
	/*XModelPieces*/ void* destroyPieces;
	PhysPreset* physPreset;
	int health;
	PhysMass mass;
	int contents;
};
struct FxSpawnDefLooping
{
	int intervalMsec;
	int count;
};

struct FxIntRange
{
	int base;
	int amplitude;
};
struct FxFloatRange
{
	float base;
	float amplitude;
};

struct FxSpawnDefOneShot
{
	FxIntRange count;
};

union FxSpawnDef
{
	FxSpawnDefLooping looping;
	FxSpawnDefOneShot oneShot;
};
struct FxElemVec3Range
{
	float base[3];
	float amplitude[3];
};

struct FxElemVelStateInFrame
{
	FxElemVec3Range velocity;
	FxElemVec3Range totalDelta;
};

const struct FxElemVelStateSample
{
	FxElemVelStateInFrame local;
	FxElemVelStateInFrame world;
};

struct FxElemVisualState
{
	char color[4];
	float rotationDelta;
	float rotationTotal;
	float size[2];
	float scale;
};

const struct FxElemVisStateSample
{
	FxElemVisualState base;
	FxElemVisualState amplitude;
};
struct FxEffectDef;

union FxEffectDefRef
{
	FxEffectDef* handle;
	const char* name;
};

union FxElemVisuals
{
	const void* anonymous;
	Material* material;
	XModel* model;
	FxEffectDefRef effectDef;
	const char* soundName;
};

struct FxElemMarkVisuals
{
	Material* materials[2];
};

union FxElemDefVisuals
{
	FxElemMarkVisuals* markArray;
	FxElemVisuals* array;
	FxElemVisuals instance;
};
enum pmeflags_t
{
	EF_TELEPORT_BIT = 0x2,
	EF_DUCKED = 0x4,
	EF_PRONE = 0x8,
	EF_NOT_STANDING = 0xC,
	EF_NODRAW = 0x20,
	EF_FIRING = 0x40,
	EF_TURRET_ACTIVE_PRONE = 0x100,
	EF_TURRET_ACTIVE_DUCK = 0x200,
	EF_TURRET_ACTIVE = 0x300,
	EF_AIM_ASSIST = 0x800,
	EF_VEHICLE_ACTIVE = 0x4000,
	EF_TIMED_OBJECT = 0x10000,
	EF_DEAD = 0x20000,
	EF_ADS = 0x40000,
	EF_VOTED = 0x100000,
	EF_TALK = 0x200000,
};

struct WeaponDef
{
	const char* szInternalName;
	const char* szDisplayName;
	const char* szOverlayName;
	XModel* gunXModel[16];
	XModel* handXModel;
	const char* szXAnims[33];
	const char* szModeName;
	unsigned __int16 hideTags[8];
	unsigned __int16 notetrackSoundMapKeys[16];
	unsigned __int16 notetrackSoundMapValues[16];
	int playerAnimType;
	weapType_t weapType;
	weapClass_t weapClass;
	PenetrateType penetrateType;
	ImpactType impactType;
	weapInventoryType_t inventoryType;
	weapFireType_t fireType;
	OffhandClass offhandClass;
	weapStance_t stance;
	FxEffectDef* viewFlashEffect;
	FxEffectDef* worldFlashEffect;
	snd_alias_list_t* pickupSound;
	snd_alias_list_t* pickupSoundPlayer;
	snd_alias_list_t* ammoPickupSound;
	snd_alias_list_t* ammoPickupSoundPlayer;
	snd_alias_list_t* projectileSound;
	snd_alias_list_t* pullbackSound;
	snd_alias_list_t* pullbackSoundPlayer;
	snd_alias_list_t* fireSound;
	snd_alias_list_t* fireSoundPlayer;
	snd_alias_list_t* fireLoopSound;
	snd_alias_list_t* fireLoopSoundPlayer;
	snd_alias_list_t* fireStopSound;
	snd_alias_list_t* fireStopSoundPlayer;
	snd_alias_list_t* fireLastSound;
	snd_alias_list_t* fireLastSoundPlayer;
	snd_alias_list_t* emptyFireSound;
	snd_alias_list_t* emptyFireSoundPlayer;
	snd_alias_list_t* meleeSwipeSound;
	snd_alias_list_t* meleeSwipeSoundPlayer;
	snd_alias_list_t* meleeHitSound;
	snd_alias_list_t* meleeMissSound;
	snd_alias_list_t* rechamberSound;
	snd_alias_list_t* rechamberSoundPlayer;
	snd_alias_list_t* reloadSound;
	snd_alias_list_t* reloadSoundPlayer;
	snd_alias_list_t* reloadEmptySound;
	snd_alias_list_t* reloadEmptySoundPlayer;
	snd_alias_list_t* reloadStartSound;
	snd_alias_list_t* reloadStartSoundPlayer;
	snd_alias_list_t* reloadEndSound;
	snd_alias_list_t* reloadEndSoundPlayer;
	snd_alias_list_t* detonateSound;
	snd_alias_list_t* detonateSoundPlayer;
	snd_alias_list_t* nightVisionWearSound;
	snd_alias_list_t* nightVisionWearSoundPlayer;
	snd_alias_list_t* nightVisionRemoveSound;
	snd_alias_list_t* nightVisionRemoveSoundPlayer;
	snd_alias_list_t* altSwitchSound;
	snd_alias_list_t* altSwitchSoundPlayer;
	snd_alias_list_t* raiseSound;
	snd_alias_list_t* raiseSoundPlayer;
	snd_alias_list_t* firstRaiseSound;
	snd_alias_list_t* firstRaiseSoundPlayer;
	snd_alias_list_t* putawaySound;
	snd_alias_list_t* putawaySoundPlayer;
	snd_alias_list_t** bounceSound;
	FxEffectDef* viewShellEjectEffect;
	FxEffectDef* worldShellEjectEffect;
	FxEffectDef* viewLastShotEjectEffect;
	FxEffectDef* worldLastShotEjectEffect;
	Material* reticleCenter;
	Material* reticleSide;
	int iReticleCenterSize;
	int iReticleSideSize;
	int iReticleMinOfs;
	activeReticleType_t activeReticleType;
	float vStandMove[3];
	float vStandRot[3];
	float vDuckedOfs[3];
	float vDuckedMove[3];
	float vDuckedRot[3];
	float vProneOfs[3];
	float vProneMove[3];
	float vProneRot[3];
	float fPosMoveRate;
	float fPosProneMoveRate;
	float fStandMoveMinSpeed;
	float fDuckedMoveMinSpeed;
	float fProneMoveMinSpeed;
	float fPosRotRate;
	float fPosProneRotRate;
	float fStandRotMinSpeed;
	float fDuckedRotMinSpeed;
	float fProneRotMinSpeed;
	XModel* worldModel[16];
	XModel* worldClipModel;
	XModel* rocketModel;
	XModel* knifeModel;
	XModel* worldKnifeModel;
	Material* hudIcon;
	weaponIconRatioType_t hudIconRatio;
	Material* ammoCounterIcon;
	weaponIconRatioType_t ammoCounterIconRatio;
	ammoCounterClipType_t ammoCounterClip;
	int iStartAmmo;
	const char* szAmmoName;
	int iAmmoIndex;
	const char* szClipName;
	int iClipIndex;
	int iMaxAmmo;
	int iClipSize;
	int shotCount;
	const char* szSharedAmmoCapName;
	int iSharedAmmoCapIndex;
	int iSharedAmmoCap;
	int damage;
	int playerDamage;
	int iMeleeDamage;
	int iDamageType;
	int iFireDelay;
	int iMeleeDelay;
	int meleeChargeDelay;
	int iDetonateDelay;
	int iFireTime;
	int iRechamberTime;
	int iRechamberBoltTime;
	int iHoldFireTime;
	int iDetonateTime;
	int iMeleeTime;
	int meleeChargeTime;
	int iReloadTime;
	int reloadShowRocketTime;
	int iReloadEmptyTime;
	int iReloadAddTime;
	int iReloadStartTime;
	int iReloadStartAddTime;
	int iReloadEndTime;
	int iDropTime;
	int iRaiseTime;
	int iAltDropTime;
	int iAltRaiseTime;
	int quickDropTime;
	int quickRaiseTime;
	int iFirstRaiseTime;
	int iEmptyRaiseTime;
	int iEmptyDropTime;
	int sprintInTime;
	int sprintLoopTime;
	int sprintOutTime;
	int nightVisionWearTime;
	int nightVisionWearTimeFadeOutEnd;
	int nightVisionWearTimePowerUp;
	int nightVisionRemoveTime;
	int nightVisionRemoveTimePowerDown;
	int nightVisionRemoveTimeFadeInStart;
	int fuseTime;
	int aiFuseTime;
	int requireLockonToFire;
	int noAdsWhenMagEmpty;
	int avoidDropCleanup;
	float autoAimRange;
	float aimAssistRange;
	float aimAssistRangeAds;
	float aimPadding;
	float enemyCrosshairRange;
	int crosshairColorChange;
	float moveSpeedScale;
	float adsMoveSpeedScale;
	float sprintDurationScale;
	float fAdsZoomFov;
	float fAdsZoomInFrac;
	float fAdsZoomOutFrac;
	Material* overlayMaterial;
	Material* overlayMaterialLowRes;
	weapOverlayReticle_t overlayReticle;
	WeapOverlayInteface_t overlayInterface;
	float overlayWidth;
	float overlayHeight;
	float fAdsBobFactor;
	float fAdsViewBobMult;
	float fHipSpreadStandMin;
	float fHipSpreadDuckedMin;
	float fHipSpreadProneMin;
	float hipSpreadStandMax;
	float hipSpreadDuckedMax;
	float hipSpreadProneMax;
	float fHipSpreadDecayRate;
	float fHipSpreadFireAdd;
	float fHipSpreadTurnAdd;
	float fHipSpreadMoveAdd;
	float fHipSpreadDuckedDecay;
	float fHipSpreadProneDecay;
	float fHipReticleSidePos;
	int iAdsTransInTime;
	int iAdsTransOutTime;
	float fAdsIdleAmount;
	float fHipIdleAmount;
	float adsIdleSpeed;
	float hipIdleSpeed;
	float fIdleCrouchFactor;
	float fIdleProneFactor;
	float fGunMaxPitch;
	float fGunMaxYaw;
	float swayMaxAngle;
	float swayLerpSpeed;
	float swayPitchScale;
	float swayYawScale;
	float swayHorizScale;
	float swayVertScale;
	float swayShellShockScale;
	float adsSwayMaxAngle;
	float adsSwayLerpSpeed;
	float adsSwayPitchScale;
	float adsSwayYawScale;
	float adsSwayHorizScale;
	float adsSwayVertScale;
	int bRifleBullet;
	int armorPiercing;
	int bBoltAction;
	int aimDownSight;
	int bRechamberWhileAds;
	float adsViewErrorMin;
	float adsViewErrorMax;
	int bCookOffHold;
	int bClipOnly;
	int adsFireOnly;
	int cancelAutoHolsterWhenEmpty;
	int suppressAmmoReserveDisplay;
	int enhanced;
	int laserSightDuringNightvision;
	Material* killIcon;
	weaponIconRatioType_t killIconRatio;
	int flipKillIcon;
	Material* dpadIcon;
	weaponIconRatioType_t dpadIconRatio;
	int bNoPartialReload;
	int bSegmentedReload;
	int iReloadAmmoAdd;
	int iReloadStartAdd;
	const char* szAltWeaponName;
	unsigned int altWeaponIndex;
	int iDropAmmoMin;
	int iDropAmmoMax;
	int blocksProne;
	int silenced;
	int iExplosionRadius;
	int iExplosionRadiusMin;
	int iExplosionInnerDamage;
	int iExplosionOuterDamage;
	float damageConeAngle;
	int iProjectileSpeed;
	int iProjectileSpeedUp;
	int iProjectileSpeedForward;
	int iProjectileActivateDist;
	float projLifetime;
	float timeToAccelerate;
	float projectileCurvature;
	XModel* projectileModel;
	weapProjExposion_t projExplosion;
	FxEffectDef* projExplosionEffect;
	int projExplosionEffectForceNormalUp;
	FxEffectDef* projDudEffect;
	snd_alias_list_t* projExplosionSound;
	snd_alias_list_t* projDudSound;
	int bProjImpactExplode;
	WeapStickinessType stickiness;
	int hasDetonator;
	int timedDetonation;
	int rotate;
	int holdButtonToThrow;
	int freezeMovementWhenFiring;
	float lowAmmoWarningThreshold;
	float parallelBounce[29];
	float perpendicularBounce[29];
	FxEffectDef* projTrailEffect;
	float vProjectileColor[3];
	guidedMissileType_t guidedMissileType;
	float maxSteeringAccel;
	int projIgnitionDelay;
	FxEffectDef* projIgnitionEffect;
	snd_alias_list_t* projIgnitionSound;
	float fAdsAimPitch;
	float fAdsCrosshairInFrac;
	float fAdsCrosshairOutFrac;
	int adsGunKickReducedKickBullets;
	float adsGunKickReducedKickPercent;
	float fAdsGunKickPitchMin;
	float fAdsGunKickPitchMax;
	float fAdsGunKickYawMin;
	float fAdsGunKickYawMax;
	float fAdsGunKickAccel;
	float fAdsGunKickSpeedMax;
	float fAdsGunKickSpeedDecay;
	float fAdsGunKickStaticDecay;
	float fAdsViewKickPitchMin;
	float fAdsViewKickPitchMax;
	float fAdsViewKickYawMin;
	float fAdsViewKickYawMax;
	float fAdsViewKickCenterSpeed;
	float fAdsViewScatterMin;
	float fAdsViewScatterMax;
	float fAdsSpread;
	int hipGunKickReducedKickBullets;
	float hipGunKickReducedKickPercent;
	float fHipGunKickPitchMin;
	float fHipGunKickPitchMax;
	float fHipGunKickYawMin;
	float fHipGunKickYawMax;
	float fHipGunKickAccel;
	float fHipGunKickSpeedMax;
	float fHipGunKickSpeedDecay;
	float fHipGunKickStaticDecay;
	float fHipViewKickPitchMin;
	float fHipViewKickPitchMax;
	float fHipViewKickYawMin;
	float fHipViewKickYawMax;
	float fHipViewKickCenterSpeed;
	float fHipViewScatterMin;
	float fHipViewScatterMax;
	float fightDist;
	float maxDist;
	const char* accuracyGraphName[2];
	float(*accuracyGraphKnots[2])[2];
	float(*originalAccuracyGraphKnots[2])[2];
	int accuracyGraphKnotCount[2];
	int originalAccuracyGraphKnotCount[2];
	int iPositionReloadTransTime;
	float leftArc;
	float rightArc;
	float topArc;
	float bottomArc;
	float accuracy;
	float aiSpread;
	float playerSpread;
	float minTurnSpeed[2];
	float maxTurnSpeed[2];
	float pitchConvergenceTime;
	float yawConvergenceTime;
	float suppressTime;
	float maxRange;
	float fAnimHorRotateInc;
	float fPlayerPositionDist;
	const char* szUseHintString;
	const char* dropHintString;
	int iUseHintStringIndex;
	int dropHintStringIndex;
	float horizViewJitter;
	float vertViewJitter;
	const char* szScript;
	float fOOPosAnimLength[2];
	int minDamage;
	int minPlayerDamage;
	float fMaxDamageRange;
	float fMinDamageRange;
	float destabilizationRateTime;
	float destabilizationCurvatureMax;
	int destabilizeDistance;
	float locationDamageMultipliers[19];
	const char* fireRumble;
	const char* meleeImpactRumble;
	float adsDofStart;
	float adsDofEnd;
};

enum $B87C0110D100A68234FECCEB9075A41E //channels
{
	CON_CHANNEL_DONT_FILTER = 0,
	CON_CHANNEL_ERROR = 1,
	CON_CHANNEL_GAMENOTIFY = 2,
	CON_CHANNEL_BOLDGAME = 3,
	CON_CHANNEL_SUBTITLE = 4,
	CON_CHANNEL_OBITUARY = 5,
	CON_CHANNEL_LOGFILEONLY = 6,
	CON_CHANNEL_CONSOLEONLY = 7,
	CON_CHANNEL_GFX = 8,
	CON_CHANNEL_SOUND = 9,
	CON_CHANNEL_FILES = 0xA,
	CON_CHANNEL_DEVGUI = 0xB,
	CON_CHANNEL_PROFILE = 0xC,
	CON_CHANNEL_UI = 0xD,
	CON_CHANNEL_CLIENT = 0xE,
	CON_CHANNEL_SERVER = 0xF,
	CON_CHANNEL_SYSTEM = 10,
	CON_CHANNEL_PLAYERWEAP = 11,
	CON_CHANNEL_AI = 12,
	CON_CHANNEL_ANIM = 13,
	CON_CHANNEL_PHYS = 14,
	CON_CHANNEL_FX = 15,
	CON_CHANNEL_LEADERBOARDS = 16,
	CON_CHANNEL_PARSERSCRIPT = 17,
	CON_CHANNEL_SCRIPT = 18,
	CON_BUILTIN_CHANNEL_COUNT = 19
};
enum errorParm_t
{
	ERR_FATAL = 0x0,
	ERR_DROP = 0x1,
	ERR_SERVERDISCONNECT = 0x2,
	ERR_DISCONNECT = 0x3,
	ERR_SCRIPT = 0x4,
	ERR_SCRIPT_DROP = 0x5,
	ERR_LOCALIZATION = 0x6,
	ERR_MAPLOADERRORSUMMARY = 0x7,
};
enum pmtype_t
{
	PM_NORMAL = 0x0,
	PM_NORMAL_LINKED = 0x1,
	PM_NOCLIP = 0x2,
	PM_UFO = 0x3,
	PM_DEAD = 0x4,
	PM_DEAD_LINKED = 0x5,
};

#endif
