#pragma once
#include "State.h"
#include "InputManager.h"

class PlayingState;

class VictoryState :
    public State
{
private:
	Button* saveGame;
	Button* mainMenu;
public:
	VictoryState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~VictoryState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void renderTxt();

	void updateInput();
};

