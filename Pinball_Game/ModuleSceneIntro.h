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

	int wall1[78] = {
		219, 43,
		186, 48,
		154, 58,
		120, 81,
		101, 101,
		81, 128,
		89, 149,
		119, 150,
		136, 139,
		137, 168,
		109, 176,
		93, 200,
		87, 237,
		92, 276,
		96, 332,
		99, 365,
		96, 376,
		86, 379,
		65, 293,
		38, 294,
		63, 395,
		30, 459,
		28, 670,
		40, 689,
		181, 808,
		223, 810,
		366, 686,
		365, 446,
		380, 445,
		378, 760,
		408, 759,
		407, 250,
		387, 186,
		371, 147,
		342, 106,
		304, 75,
		274, 58,
		241, 48,
		219, 44
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
