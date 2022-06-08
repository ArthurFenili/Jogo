#pragma once

#include <ctime>
#include <stack>
#include "Player.h"
#include "Phase.h"
#include "Enemy.h"
//#include "EnemyProjectile.h"
#include "EntityList.h"
#include "State.h"
#include "MainMenuState.h"

enum types {
	FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, ENEMY = 9, PLAYER = 10, SWORD = 11
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

	void update();
	void updateSFMLEvents();
	void updateDeltaTime();

	void render();

	void execute();
};
