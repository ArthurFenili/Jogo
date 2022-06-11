#pragma once

#include <stack>
#include "MainMenuState.h"

enum types {
	FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, PLAYER = 9, SWORD = 10, SKELETON = 11, ARCHER = 12
};

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
