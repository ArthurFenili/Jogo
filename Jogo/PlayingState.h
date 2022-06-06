#pragma once
#include "State.h"
#include "Player.h"
#include "Phase.h"
#include "PauseState.h"

class PlayingState :
    public State
{
private:
	Player* player1;

	Phase phase1;

	bool exit;
public:
	PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~PlayingState();

	void createMap();

	void initPlayers();
	void initEnemies();

	void updateCollision();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

