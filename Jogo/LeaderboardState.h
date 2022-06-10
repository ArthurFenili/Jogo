#pragma once
#include "State.h"
#include <vector>
#include <fstream>
#include<sstream>
class LeaderboardState :
    public State
{
private:
	Button* backButton;

	std::vector<sf::Text*> vectorString;
	std::vector<sf::Text*>::iterator iterator;

public:
	LeaderboardState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	~LeaderboardState();

	void initButtons();

	void buildLeaderboard();
	void renderLeaderboard();

	void updateButtons();
	void renderButtons();

	void updateInput();

	void render();
};

