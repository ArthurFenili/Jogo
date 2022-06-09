#pragma once
#include "State.h"
#include "NewGameState.h"
#include "LeaderboardState.h"

class MainMenuState :
	public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* newGameButton;
	Button* continueButton;
	Button* leaderboardButton;
	Button* exitButton;
public:
	MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~MainMenuState();

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

