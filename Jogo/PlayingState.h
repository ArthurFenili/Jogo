#pragma once
#include "Game.h"
#include "State.h"
#include "Player.h"
#include "Skeleton.h"
#include "ForestPhase.h"
#include "CastlePhase.h"
#include "PauseState.h"
#include "GameOverState.h"

class PlayingState :
	public State
{
private:
	Player* player1;

	Phase* currentPhase;

	bool exit;

	int score;
public:
	PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~PlayingState();

	void createMap();
	void createObstacles(int phase);
	void createEnemies(int phase);
	void createPlayers();

	void updateCollision();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();

	void changeLevel();

	void setPhase(Phase* phase) { this->currentPhase = phase; }
	Phase* getPhase() { return this->currentPhase; }
};
