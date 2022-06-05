#pragma once
#include "State.h"
#include "Player.h"
#include "Phase.h"

class PlayingState :
    public State
{
private:
	Player* player1;

	Phase phase1;
public:
	PlayingState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~PlayingState();

	void createMap();
	void initPlayers();
	void initEnemies();

	virtual void updateInput();
	void updateCollision();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

