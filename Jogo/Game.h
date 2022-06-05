#pragma once

#include <ctime>
#include <stack>
#include "Player.h"
#include "Phase.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "EntitiesList.h"
#include "State.h"
#include "MainMenuState.h"

class Game
{
private:
	GraphicsManager graphicsManager;

	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

	//-----
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

