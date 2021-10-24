#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> walls;
	p2List<PhysBody*> leftflipper_b;
	p2List<PhysBody*> rightflipper_b;
	

	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* backgroud;
	SDL_Texture* leftflipper;
	SDL_Texture* rightflipper;


	PhysBody* pb_leftFlipper;
	PhysBody* pb_rightFlipper;

	float angularSpeed;
	float maxAngle;
	float minAngle;
	float angleMargin;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	int wall1[84] = {
	406, 760,
	406, 251,
	396, 206,
	382, 173,
	359, 128,
	319, 85,
	273, 57,
	242, 46,
	211, 44,
	184, 45,
	154, 56,
	130, 72,
	112, 87,
	96, 106,
	83, 125,
	69, 151,
	124, 151,
	136, 140,
	136, 168,
	123, 167,
	110, 181,
	98, 195,
	90, 211,
	88, 237,
	88, 262,
	89, 288,
	94, 321,
	99, 357,
	99, 372,
	94, 378,
	86, 376,
	66, 294,
	36, 293,
	63, 398,
	31, 459,
	30, 678,
	178, 811,
	225, 811,
	373, 678,
	371, 454,
	377, 451,
	378, 761
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
};
