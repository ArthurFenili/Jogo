#pragma once
#include "State.h"
class PauseState :
	public State
{
private:
	Button* continueButton;
	Button* saveButton;
	Button* exitButton;

	bool* exitGame;
public:
	PauseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool* exit);
	~PauseState();

	void initButtons();

	void updateButtons();
	void renderButtons();

	void updateInput();
};

