#pragma once

#include <ctime>
#include "Phase.h"

class Game
{
private:
	GraphicsManager graphicsManager;

	Player* player1;

	Phase phase1;

	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

	enum types {
		PHASE = 0, FIRE = 1, TELEPORT = 2, SLOW = 3, BLOCK = 4, DOOR = 5, BACKGROUND = 6, ENEMY = 7, PLAYER = 8, SWORD = 9
	};

public:
	Game();
	~Game();

	void update();
	void updateSFMLEvents();
	void updateDeltaTime();
	void updateCollision();

	void render();

	void execute();
};
