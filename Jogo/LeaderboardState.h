#pragma once
#include "State.h"
#include <vector>
#include <fstream>
#include<sstream>
class LeaderboardState :
    public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::Font font;
	Button* backButton;

	std::vector<sf::Text*> vectorString;
	std::vector<sf::Text*>::iterator iterator;

public:
	LeaderboardState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~LeaderboardState();

	void initBackground();
	void initFonts();
	void initButtons();

	void buildLeaderboard();
	void renderLeaderboard();

	void updateButtons();
	void renderButtons();

	virtual void updateInput();
	virtual void update(float dt);
	virtual void render();
	virtual void resetState();
};

