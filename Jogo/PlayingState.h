#pragma once
#include "Game.h"
#include "State.h"
#include "Player.h"
#include "Skeleton.h"
#include "ForestPhase.h"
#include "CastlePhase.h"
#include "PauseState.h"
#include "GameOverState.h"
#include <time.h>

class PlayingState :
	public State
{
private:
	Player* player1;

	Player* player2;

	Phase* currentPhase;

	bool exit;

	static int score;
public:
	static bool twoPlayers;

public:
	PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool twoP);
	~PlayingState();

	void createMap();
	void createObstacles(int phase);
	void createEnemies(int phase);
	void createPlayers();

	static int getScore() { return score; }
	static void setScore(int points) { score += points; }

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();

	void changeLevel();

	void setPhase(Phase* phase) { this->currentPhase = phase; }
	Phase* getPhase() { return this->currentPhase; }
};
