#pragma once
#include "State.h"
#include "PlayingState.h"
class NewGameState :
	public State
{
private:
	Button* onePlayerButton;
	Button* twoPlayersButton;
	Button* backButton;
public:
	NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~NewGameState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void updateInput();
};

