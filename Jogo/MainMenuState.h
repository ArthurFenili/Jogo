#pragma once
#include "State.h"
#include "SelectPhaseState.h"
#include "LeaderboardState.h"

class MainMenuState :
	public State
{
private:
	Button* newGameButton;
	Button* continueButton;
	Button* leaderboardButton;
	Button* exitButton;
public:
	MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~MainMenuState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void updateInput();
};