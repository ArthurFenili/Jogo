#pragma once
#include "State.h"
#include "NewGameState.h"
class MainMenuState :
    public State
{
private:
	sf::RectangleShape background;
public:
	MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~MainMenuState();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

