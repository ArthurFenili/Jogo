#pragma once
#include "State.h"
#include <vector>
#include <fstream>
class LeaderboardState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* backButton;

public:
	LeaderboardState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~LeaderboardState();

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

