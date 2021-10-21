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

	circle = App->textures->Load("pinball/ball.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	backgroud = App->textures->Load("pinball/pinballtemplate.png");

	PhysBody* pb_wall1 = App->physics->CreateStaticChain(0, 0, wall1, 78);
	PhysBody* pb_wall2 = App->physics->CreateStaticChain(0, 0, wall2, 14);
	PhysBody* pb_wall3 = App->physics->CreateStaticChain(0, 0, wall3, 14);
	PhysBody* pb_wall4 = App->physics->CreateStaticChain(0, 0, wall4, 10);
	PhysBody* pb_wall5 = App->physics->CreateStaticChain(0, 0, wall5, 56);
	PhysBody* pb_wall6 = App->physics->CreateStaticChain(0, 0, wall6, 14);
	PhysBody* pb_wall7 = App->physics->CreateStaticChain(0, 0, wall7, 14);
	PhysBody* pb_wall8 = App->physics->CreateStaticChain(0, 0, wall8, 10);

	walls.add(pb_wall1);
	walls.add(pb_wall2);
	walls.add(pb_wall3);
	walls.add(pb_wall4);
	walls.add(pb_wall5);
	walls.add(pb_wall6);
	walls.add(pb_wall7);
	walls.add(pb_wall8);

	pb_leftFlipper = App->physics->CreateKinematicChain(0, 0, leftFlipper, 24);
	pb_rightFlipper = App->physics->CreateKinematicChain(255, 731, rightFlipper, 20);


	angleMargin = 10.0f;
	angularSpeed = 15.0f;
	minAngle = 0.0f;
	maxAngle = 60.0f;

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

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_STATE::KEY_REPEAT)
	{
		if (pb_leftFlipper->body->GetAngle() - DEGTORAD * angularSpeed > -DEGTORAD * maxAngle)
		{
			pb_leftFlipper->body->SetAngularVelocity(-angularSpeed);
		}

		if (pb_leftFlipper->body->GetAngle() - DEGTORAD * angularSpeed < -DEGTORAD * maxAngle)
		{
			pb_leftFlipper->body->SetAngularVelocity(0.0f);
		}
	}
	else
	{
		if (pb_leftFlipper->body->GetAngle() < 0.0f)
		{
			if (pb_leftFlipper->body->GetAngle() < DEGTORAD * minAngle + DEGTORAD * angleMargin)
			{
				pb_leftFlipper->body->SetAngularVelocity(angularSpeed);
			}

		}

		if (pb_leftFlipper->body->GetAngle() + DEGTORAD * angularSpeed > DEGTORAD * minAngle + DEGTORAD * angleMargin)
		{
			pb_leftFlipper->body->SetAngularVelocity(0.0f);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_STATE::KEY_REPEAT)
	{
		if (pb_rightFlipper->body->GetAngle() + DEGTORAD * angularSpeed < DEGTORAD * maxAngle)
		{
			pb_rightFlipper->body->SetAngularVelocity(angularSpeed);
		}

		if (pb_rightFlipper->body->GetAngle() + DEGTORAD * angularSpeed > DEGTORAD * maxAngle)
		{
			pb_rightFlipper->body->SetAngularVelocity(0.0f);
		}
	}
	else
	{
		if (pb_rightFlipper->body->GetAngle() > 0.0f)
		{
			if (pb_rightFlipper->body->GetAngle() > DEGTORAD * minAngle - DEGTORAD * angleMargin)
			{
				pb_rightFlipper->body->SetAngularVelocity(-angularSpeed);
			}
		}

		if (pb_rightFlipper->body->GetAngle() - DEGTORAD * angularSpeed < DEGTORAD * minAngle - DEGTORAD * angleMargin)
		{
			pb_rightFlipper->body->SetAngularVelocity(0.0f);
		}
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
