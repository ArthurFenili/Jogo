#pragma once
#include "State.h"
#include "PlayingState.h"
class NewGameState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* onePlayerButton;
	Button* twoPlayersButton;
	Button* backButton;
public:
	NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~NewGameState();

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

