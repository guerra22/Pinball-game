#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	backgroud = App->textures->Load("pinball/pinballtemplate.png");

	int pinballtemplate[78] = {
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
    App->physics->CreateChain(0, 0, pinballtemplate, 78);

	int pinballtemplate2[14] = {
		255, 722,
		259, 726,
		342, 650,
		343, 504,
		340, 505,
		339, 649,
		257, 718
	};
	App->physics->CreateChain(0, 0, pinballtemplate2, 14);
	
	int pinballtemplate3[14] = {
		272, 642,
		273, 646,
		316, 609,
		315, 536,
		310, 541,
		313, 607,
		275, 640
	};
	App->physics->CreateChain(0, 0, pinballtemplate3, 14);
	
	int pinballtemplate4[10] = {
	246, 581,
	255, 586,
	283, 561,
	282, 516,
	248, 577
	};
	App->physics->CreateChain(0, 0, pinballtemplate4, 10);
	
	int pinballtemplate5[56] = {
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
	App->physics->CreateChain(0, 0, pinballtemplate5, 56);
	
	int pinballtemplate6[14] = {
	59, 661,
	58, 511,
	66, 511,
	65, 653,
	151, 730,
	144, 736,
	59, 662
	};
	App->physics->CreateChain(0, 0, pinballtemplate6, 14);
	
	int pinballtemplate7[14] = {
	129, 655,
	133, 649,
	93, 614,
	93, 548,
	89, 544,
	89, 615,
	126, 653
	};
	App->physics->CreateChain(0, 0, pinballtemplate7, 14);

	int pinballtemplate8[10] = {
	120, 518,
	154, 582,
	147, 586,
	118, 562,
	119, 521
	};

	App->physics->CreateChain(0, 0, pinballtemplate8, 10);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));
		circles.getLast()->data->listener = this;
	}

	
	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	App->renderer->Blit(backgroud, 0, 0, NULL, 1.0f, 0);
	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
