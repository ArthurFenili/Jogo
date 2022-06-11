#pragma once
#include "Game.h"
#include "State.h"
#include "Player.h"
#include "Skeleton.h"
#include "ForestPhase.h"
#include "CastlePhase.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include <time.h>

class PlayingState :
	public State
{
private:
	Player* player1;

	Player* player2;

	Phase* currentPhase;

	bool exit;


public:
	static int score;
	static bool forestPhase;
	static bool twoPlayers;
	static bool enteredDoor;
	static bool defeatedBoss;

public:
	PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~PlayingState();

	void createMap();
	void createObstacles(int phase);
	void createEnemies(int phase);
	void createPlayers();

	void updateInput();
	void update(float dt);
	void render();

	void changeLevel();

	void setPhase(Phase* phase) { this->currentPhase = phase; }
	Phase* getPhase() { return this->currentPhase; }
};