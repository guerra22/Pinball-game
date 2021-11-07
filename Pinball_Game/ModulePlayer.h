#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	int playerLives = 3;
	int ballsInGame = 1;
	int lastscore = 0;
	int highestscore = 0;
	int score = 0;
	void RestartPlayer()
	{
		score = 0;
		playerLives = 3;
		ballsInGame = 1;
	}

public:

};