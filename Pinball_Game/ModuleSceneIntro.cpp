#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

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
	backgroud = App->textures->Load("pinball/pinballtemplate.png");
	leftflipper = App->textures->Load("pinball/leftflipper.png");
	rightflipper = App->textures->Load("pinball/rightflipper.png");
	spring = App->textures->Load("pinball/spring.png");
	pausescreen = App->textures->Load("pinball/pause.png");
	startscreen = App->textures->Load("pinball/play.png");
	endscreen = App->textures->Load("pinball/end.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	start_fx = App->audio->LoadFx("pinball/start.wav");
	lose_fx = App->audio->LoadFx("pinball/lose.wav");
	collide_fx = App->audio->LoadFx("pinball/collide.wav");
	bg_music = App->audio->LoadFx("pinball/music.ogg");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	pauseFont = App->fonts->Load("Fonts/rtype_font.png", lookupTable, 1);
	char lookupTable1[] = { "0123456789 0123456789" };
	livesFont = App->fonts->Load("Fonts/Score1.png", lookupTable1, 2);

	PhysBody* pb_wall1 = App->physics->CreateStaticChain(0, 0, wall1, 86);
	PhysBody* pb_wall2 = App->physics->CreateStaticChain(0, 0, wall2, 14);
	PhysBody* pb_wall3 = App->physics->CreateStaticChain(0, 0, wall3, 14);
	PhysBody* pb_wall4 = App->physics->CreateStaticChain(0, 0, wall4, 10);
	PhysBody* pb_wall5 = App->physics->CreateStaticChain(0, 0, wall5, 56);
	PhysBody* pb_wall6 = App->physics->CreateStaticChain(0, 0, wall6, 14);
	PhysBody* pb_wall7 = App->physics->CreateStaticChain(0, 0, wall7, 14);
	PhysBody* pb_wall8 = App->physics->CreateStaticChain(0, 0, wall8, 10);

	PhysBody* pb_ballStartPositionerLeft = App->physics->CreateStaticChain(0, 0, ballStartPositionerLeft, 6);
	PhysBody* pb_ballStartPositionerRight = App->physics->CreateStaticChain(0, 0, ballStartPositionerRight, 6);

	bumper01.x = 214;
	bumper01.y = 269;
	bumper01.radius = 21;

	bumper02.x = 158;
	bumper02.y = 346;
	bumper02.radius = 21;

	bumper03.x = 275;
	bumper03.y = 347;
	bumper03.radius = 21;

	bumper04.x = 114;
	bumper04.y = 124;
	bumper04.radius = 24;

	PhysBody* scorehitbox1 = App->physics->CreateStaticCircle(179, 148, 20);
	PhysBody* scorehitbox2 = App->physics->CreateStaticCircle(243, 148, 20);
	PhysBody* scorehitbox3 = App->physics->CreateStaticCircle(305, 148, 20);
	

	pb_bumper01 = App->physics->CreateSensorCircle(bumper01.x, bumper01.y, bumper01.radius);
	pb_bumper02 = App->physics->CreateSensorCircle(bumper02.x, bumper02.y, bumper02.radius);
	pb_bumper03 = App->physics->CreateSensorCircle(bumper03.x, bumper03.y, bumper03.radius);
	pb_bumper04 = App->physics->CreateSensorCircle(bumper04.x, bumper04.y, bumper04.radius);

	PhysBody* pb_bumper01Interior = App->physics->CreateStaticCircle(bumper01.x, bumper01.y, bumper01.radius - 2);
	PhysBody* pb_bumper02Interior = App->physics->CreateStaticCircle(bumper02.x, bumper02.y, bumper02.radius - 2);
	PhysBody* pb_bumper03Interior = App->physics->CreateStaticCircle(bumper03.x, bumper03.y, bumper03.radius - 2);
	PhysBody* pb_bumper04Interior = App->physics->CreateStaticCircle(bumper04.x, bumper04.y, bumper04.radius - 2);

	pb_rightLateralBumper = App->physics->CreateKinematicRectangle(262, 550, 1, 71);
	pb_rightLateralBumper->body->SetTransform(pb_rightLateralBumper->body->GetPosition(), 27 * DEGTORAD);
	pb_rightLateralBumper->body->GetFixtureList()->SetSensor(true);

	pb_leftLateralBumper = App->physics->CreateKinematicRectangle(138, 550, 1, 71);
	pb_leftLateralBumper->body->SetTransform(pb_leftLateralBumper->body->GetPosition(), -27 * DEGTORAD);
	pb_leftLateralBumper->body->GetFixtureList()->SetSensor(true);

	ballLauncherRectangle = App->physics->CreateKinematicRectangle(393, 774, 25, 40); 
	ballLauncherRecInitPosX = ballLauncherRectangle->body->GetPosition().x;
	ballLauncherRecInitPosY = ballLauncherRectangle->body->GetPosition().y;

	hitbox.add(scorehitbox1);
	hitbox.add(scorehitbox2);
	hitbox.add(scorehitbox3);
	
	bumpers.add(pb_bumper01);
	bumpers.add(pb_bumper02);
	bumpers.add(pb_bumper03);
	bigbumper.add(pb_bumper04);

	walls.add(pb_wall1);
	walls.add(pb_wall2);
	walls.add(pb_wall3);
	walls.add(pb_wall4);
	walls.add(pb_wall5);
	walls.add(pb_wall6);
	walls.add(pb_wall7);
	walls.add(pb_wall8);

	pb_leftFlipper = App->physics->CreateKinematicChain(153, 733, leftFlipper, 20);
	leftflipper_b.add(pb_leftFlipper);
	pb_rightFlipper = App->physics->CreateKinematicChain(255, 733, rightFlipper, 20);
	rightflipper_b.add(pb_rightFlipper);
	circles.add(App->physics->CreateCircle(392, 732, 10));
	circles.getLast()->data->listener = this;

	angleMargin = 10.0f;
	angularSpeed = 20.0f;
	minAngle = 0.0f;
	maxAngle = 70.0f;
	bumperForce = 8.0f;
	bigbumperForce = 3.0f;
	lateralBumperForce = 13.0f;

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
	//App->audio->PlayFx(bg_music);
	/*if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) App->physics->joint->SetMotorSpeed(100.0f);
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP) App->physics->joint->SetMotorSpeed(-100.0f);*/
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_STATE::KEY_DOWN)
	{
		startForce = 0;
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_STATE::KEY_REPEAT)
	{
		if (startForce < 0.5f)
		{
			startForce += 0.005f;
		}
		b2Vec2 relativePos = { ballLauncherRecInitPosX , ballLauncherRecInitPosY + startForce };
		ballLauncherRectangle->body->SetTransform(relativePos, 0.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_STATE::KEY_UP)
	{
		float y1 = METERS_TO_PIXELS(ballLauncherRecInitPosY);
		float y2 = METERS_TO_PIXELS(ballLauncherRectangle->body->GetPosition().y);

		b2Vec2 force = { 0,-(y2 - y1 + startForce * 2) };
		ballLauncherRectangle->body->SetLinearVelocity(force);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_STATE::KEY_IDLE)
	{
		if (METERS_TO_PIXELS(ballLauncherRectangle->body->GetPosition().y) < 750)
		{
			b2Vec2 zeroSpeed = { 0,0 };
			ballLauncherRectangle->body->SetLinearVelocity(zeroSpeed);
			b2Vec2 initPos = { ballLauncherRecInitPosX,ballLauncherRecInitPosY };
			ballLauncherRectangle->body->SetTransform(initPos, 0.0f);
		}
	}

	App->renderer->Blit(backgroud, 0, 0, NULL, 1.0f, 0);
	App->renderer->Blit(spring, 378, (METERS_TO_PIXELS(ballLauncherRectangle->body->GetPosition().y) - 21), nullptr);

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_UP)
		gamePaused = !gamePaused;
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		end = false;
		App->player->RestartPlayer();
		ResetBallPos();
		App->physics->b1->SetTransform(b2Vec2(PIXEL_TO_METERS(493), PIXEL_TO_METERS(450)), App->physics->b1->GetAngle());
	}
	if (!gamePaused && App->player->playerLives != 0)
	{
		App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 4, pauseFont, "player life ");
		sprintf_s(livesText, 10, "%d", App->player->playerLives);
		App->fonts->BlitText(SCREEN_WIDTH / 2 + 8, SCREEN_HEIGHT / 2, livesFont, livesText);
		
		App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 16, pauseFont, "player score ");
		sprintf_s(livesText, 10, "%5d", App->player->score);
		App->fonts->BlitText(SCREEN_WIDTH / 2 + 8, SCREEN_HEIGHT / 2 + 12, livesFont, livesText);

		App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 28, pauseFont, "last socre ");
		sprintf_s(livesText, 10, "%5d", App->player->lastscore);
		App->fonts->BlitText(SCREEN_WIDTH / 2 + 8, SCREEN_HEIGHT / 2 + 24, livesFont, livesText);

		App->fonts->BlitText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 40, pauseFont, "highest score ");
		sprintf_s(livesText, 10, "%5d", App->player->highestscore);
		App->fonts->BlitText(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT / 2 + 36, livesFont, livesText);

		circles.getFirst()->data->body->SetType(b2_dynamicBody);

		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
		{
			ray_on = !ray_on;
			ray.x = App->input->GetMouseX();
			ray.y = App->input->GetMouseY();
		}
		
		/*if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10));
			circles.getLast()->data->listener = this;
		}*/
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
	}
	else if(gamePaused){
		circles.getFirst()->data->body->SetType(b2_staticBody);
		//App->fonts->BlitText(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2, pauseFont, "pause ");
		App->renderer->Blit(pausescreen, 0, 0, NULL, 1.0f, 0);
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	//App->renderer->Blit(leftflipper, 146, 727, NULL, 1.0f, 0);
	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();
	
	//App->physics->b1->SetTransform(b2Vec2(PIXEL_TO_METERS(393), PIXEL_TO_METERS(450)), App->physics->b1->GetAngle());
	

	while (c != NULL)
	{

		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());

		if (y > 780) {
			App->player->playerLives--;
			App->physics->b1->SetTransform(b2Vec2(PIXEL_TO_METERS(493), PIXEL_TO_METERS(450)), App->physics->b1->GetAngle());
			ResetBallPos();
		}
		
		if (App->player->playerLives > 0)
		{
			if (y < 400) App->physics->b1->SetTransform(b2Vec2(PIXEL_TO_METERS(420), PIXEL_TO_METERS(450)), App->physics->b1->GetAngle());
		}
		else App->physics->b1->SetTransform(b2Vec2(PIXEL_TO_METERS(393), PIXEL_TO_METERS(450)), App->physics->b1->GetAngle());

		c = c->next;
	}

	if (pb_leftLateralBumper->body->GetContactList() != nullptr)
	{
		if (pb_leftLateralBumper->body->GetContactList()->contact->IsTouching())
		{
			b2Body* ball = pb_leftLateralBumper->body->GetContactList()->contact->GetFixtureB()->GetBody();

			b2Vec2 bumpForceVec = { 24, -35 };

			bumpForceVec.Normalize();
			bumpForceVec *= lateralBumperForce;

			ball->SetLinearVelocity(bumpForceVec);
		}
	}

	if (pb_rightLateralBumper->body->GetContactList() != nullptr)
	{
		if (pb_rightLateralBumper->body->GetContactList()->contact->IsTouching())
		{
			b2Body* ball = pb_rightLateralBumper->body->GetContactList()->contact->GetFixtureB()->GetBody();

			b2Vec2 bumpForceVec = { -24, -35 };
			bumpForceVec.Normalize();
			bumpForceVec *= lateralBumperForce;

			ball->SetLinearVelocity(bumpForceVec);
			App->player->score += 50;
		}
	}

	p2List_item <PhysBody*>* bumperPointer = bumpers.getFirst();
	while (bumperPointer != nullptr)
	{
		if (bumperPointer->data->body->GetContactList() != nullptr)
		{
			if (bumperPointer->data->body->GetContactList()->contact->IsTouching())
			{
				b2Body* ball = bumperPointer->data->body->GetContactList()->contact->GetFixtureB()->GetBody();

				b2Vec2 bumpForceVec = {
					ball->GetPosition().x - bumperPointer->data->body->GetPosition().x,
					ball->GetPosition().y - bumperPointer->data->body->GetPosition().y
				};

				bumpForceVec.Normalize();
				bumpForceVec *= bumperForce;

				ball->SetLinearVelocity(bumpForceVec);

				App->audio->PlayFx(bonus_fx);

				App->player->score += 100;
				//playerscore
				LOG("SCORE: %i", App->player->score);
				//LOG("x: %f, y: %f", bumpForceVec.x, bumpForceVec.y);


			}
		}

		bumperPointer = bumperPointer->next;
	}

	p2List_item <PhysBody*>* bigbumperPointer = bigbumper.getFirst();
	while (bigbumperPointer != nullptr)
	{
		if (bigbumperPointer->data->body->GetContactList() != nullptr)
		{
			if (bigbumperPointer->data->body->GetContactList()->contact->IsTouching())
			{
				b2Body* ball = bigbumperPointer->data->body->GetContactList()->contact->GetFixtureB()->GetBody();

				b2Vec2 bigbumpForceVec = {
					ball->GetPosition().x - bigbumperPointer->data->body->GetPosition().x,
					ball->GetPosition().y - bigbumperPointer->data->body->GetPosition().y
				};

				bigbumpForceVec.Normalize();
				bigbumpForceVec *= bigbumperForce;

				ball->SetLinearVelocity(bigbumpForceVec);

				App->audio->PlayFx(collide_fx);
				App->player->score += 100;
			}
		}

		bigbumperPointer = bigbumperPointer->next;
	}
	
	App->renderer->Blit(leftflipper, 146, 727, NULL, 1.0f, leftflipper_b.getFirst()->data->GetRotation(), 7, 6);
	App->renderer->Blit(rightflipper, 215, 727, NULL, 1.0f, rightflipper_b.getFirst()->data->GetRotation(), 40, 6);
	
	if (play == true) {
		App->renderer->Blit(startscreen, 0, 0, NULL, 1.0f, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		play = !play;
	if (App->player->playerLives == 0) {
		end = true;
		App->player->lastscore = App->player->score;
		if (App->player->score >= App->player->highestscore) {
			App->player->highestscore = App->player->score;
		}
	}
	if (end == true) {
		fx_on = true;
		App->renderer->Blit(endscreen, 0, 0, NULL, 1.0f, 0);
		if (fx_on)
		{
			App->audio->PlayFx(lose_fx);
			fx_on = false;
		}
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

	//App->audio->PlayFx(bonus_fx);

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

void ModuleSceneIntro::ResetBallPos() {
	fx_on = true;
	App->physics->world->DestroyBody(circles.getFirst()->data->body);
	circles.add(App->physics->CreateCircle(392, 732, 10));
	if (fx_on)
	{
		App->audio->PlayFx(start_fx);
		fx_on = false;
	}
	circles.getLast()->data->listener = this;
}
