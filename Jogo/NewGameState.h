#pragma once
#include "State.h"
#include "PlayingState.h"
class NewGameState :
    public State
{
private:
	sf::RectangleShape background;
public:
	NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~NewGameState();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

