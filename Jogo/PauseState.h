#pragma once
#include "State.h"
class PauseState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* continueButton;
	Button* saveButton;
	Button* exitButton;

	bool* exitGame;
public:
	PauseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool* exit);
	~PauseState();

	void initBackground();
	void initFonts();
	void initButtons();

	void updateButtons();
	void renderButtons();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

