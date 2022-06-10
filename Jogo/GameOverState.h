#pragma once
#include "State.h"
#include "InputManager.h"
#include <fstream>

class PlayingState;

class GameOverState :
	public State
{
private:
	Button* playAgain;
	Button* saveGame;
	Button* mainMenu;

	InputManager inputManager;
	std::string name;
public:
	GameOverState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~GameOverState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void updateInput();

	void writeToLeaderboardFile();
};

