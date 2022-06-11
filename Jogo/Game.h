#pragma once

#include <stack>
#include "MainMenuState.h"

class Game
{
private:
	GraphicsManager graphicsManager;

	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

public:
	Game();
	~Game();

	void initStates();

	void execute();

	void updateDeltaTime();
	void update();
	void updateSFMLEvents();

	void render();
};
