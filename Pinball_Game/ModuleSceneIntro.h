#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

struct bumper_def
{
	int x;
	int y;
	int radius;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void ResetBallPos();

	int GetCenterX(SDL_Rect r)
	{
		return  r.x + r.w / 2;
	}
	int GetCenterY(SDL_Rect r)
	{
		return  r.y + r.h / 2;
	}
public:
	bumper_def bumper01;
	bumper_def bumper02;
	bumper_def bumper03;
	bumper_def bumper04;
	PhysBody* pb_bumper01;
	PhysBody* pb_bumper02;
	PhysBody* pb_bumper03;
	PhysBody* pb_bumper04;
	PhysBody* pb_rightLateralBumper;
	PhysBody* pb_leftLateralBumper;
    PhysBody* ballLauncherRectangle;

	float ballLauncherRecInitPosX;
	float ballLauncherRecInitPosY;
	float lateralBumperForce;
	float bumperForce;
	float bigbumperForce;

	p2List<PhysBody*> circles;
	p2List<PhysBody*> walls;
	p2List<PhysBody*> leftflipper_b;
	p2List<PhysBody*> rightflipper_b;
	p2List<PhysBody*> hitbox;
	p2List<PhysBody*> bumpers;
	p2List<PhysBody*> bigbumper;
	
	bool gamePaused = false;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* backgroud;
	SDL_Texture* leftflipper;
	SDL_Texture* rightflipper;
	SDL_Texture* spring;
	SDL_Texture* pausescreen;
	SDL_Texture* startscreen;
	SDL_Texture* endscreen;


	uint pause = 000;
	int pauseFont = -1;
	char pauseText[10] = { "\0" };

	uint lives = 0000;
	int livesFont = -1;
	char livesText[10] = { "\0" };

	PhysBody* pb_leftFlipper;
	PhysBody* pb_rightFlipper;

	float angularSpeed;
	float maxAngle;
	float minAngle;
	float angleMargin;

	bool play = true;
	bool end = false;

	uint bonus_fx;
	uint start_fx;
	uint collide_fx;
	uint lose_fx;
	uint bg_music;

	bool fx_on = true;

	p2Point<int> ray;
	bool ray_on;

	int wall1[86] = {
	407, 774,
	407, 251,
	402, 224,
	394, 198,
	382, 170,
	370, 145,
	352, 117,
	327, 92,
	305, 74,
	278, 58,
	251, 47,
	226, 43,
	197, 43,
	177, 47,
	154, 56,
	129, 71,
	113, 86,
	94, 108,
	79, 132,
	69, 151,
	122, 151,
	130, 147,
	136, 133,
	136, 167,
	122, 168,
	105, 176,
	89, 211,
	89, 267,
	92, 313,
	100, 370,
	95, 376,
	87, 377,
	66, 294,
	37, 294,
	64, 397,
	31, 459,
	29, 682,
	175, 813,
	225, 813,
	371, 681,
	372, 453,
	378, 448,
	378, 774
	};
	int wall2[14] = {
		255, 727,
		259, 731,
		342, 655,
		343, 509,
		340, 510,
		339, 654,
		257, 723
	};
	int wall3[14] = {
		272, 642,
		273, 646,
		316, 609,
		315, 536,
		310, 541,
		313, 607,
		275, 640
	};
	int wall4[10] = {
	246, 581,
	255, 586,
	283, 561,
	282, 516,
	248, 577
	};
	int wall5[56] = {
	342, 379,
	342, 384,
	353, 385,
	357, 376,
	366, 354,
	374, 328,
	376, 310,
	379, 276,
	380, 257,
	374, 228,
	366, 204,
	354, 185,
	333, 165,
	321, 154,
	318, 168,
	328, 168,
	333, 175,
	313, 213,
	324, 222,
	342, 184,
	352, 193,
	359, 202,
	359, 226,
	358, 264,
	356, 287,
	353, 307,
	350, 327,
	343, 374
	};
	int wall6[14] = {
	59, 661,
	58, 511,
	66, 511,
	65, 653,
	151, 730,
	144, 736,
	59, 662
	};
	int wall7[14] = {
	129, 655,
	133, 649,
	93, 614,
	93, 548,
	89, 544,
	89, 615,
	126, 653
	};
	int wall8[10] = {
	120, 518,
	154, 582,
	147, 586,
	118, 562,
	119, 521
	};

	int rightRedIsland[12] = {
	772, 1570,
	798, 1593,
	896, 1556,
	903, 1340,
	869, 1363,
	784, 1553
	};
	int leftRedIsland[12] = {
	300, 1570,
	208, 1368,
	180, 1340,
	172, 1556,
	273, 1597,
	301, 1578
	};

	int leftFlipper[20] = {
	-6, -4,
	-2, -7,
	4, -6,
	34, 14,
	39, 18,
	40, 22,
	36, 24,
	30, 22,
	-2, 6,
	-7, 2
	};
	int rightFlipper[20] = {
	5, 5,
	0, -7,
	-5, -5,
	-38, 16,
	-40, 18,
	-40, 22,
	-36, 23,
	-33, 22,
	0, 7,
	6, 2
	};
	int ballStartPositionerLeft[6]
	{
		378, 746,
		378, 755,
		383, 755
	};

	int ballStartPositionerRight[6]
	{
		407, 746,
		407, 755,
		402, 755
	};
	float startForce;
};