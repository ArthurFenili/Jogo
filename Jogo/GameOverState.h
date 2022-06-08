#pragma once
#include "State.h"

class PlayingState;

class GameOverState :
	public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* playAgain;
	Button* saveGame;
	Button* mainMenu;
public:
	GameOverState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~GameOverState();

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

