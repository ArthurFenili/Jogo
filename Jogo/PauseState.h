#pragma once
#include "State.h"
#include "Phase.h"

class PlayingState;

class PauseState :
	public State
{
private:
	Button* continueButton;
	Button* saveButton;
	Button* exitButton;

	bool* exitGame;

	Phase* currentPhase;
	EntityList* entityList;
public:
	PauseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool* exit, Phase* currentPhase);
	~PauseState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void updateInput();

	void writeToSavedGameFile();
};

