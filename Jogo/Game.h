#pragma once

#include <ctime>
#include "Player.h"
#include "Phase.h"
#include "Enemy.h"
#include "EnemyProjectile.h"
#include "EntitiesList.h"

class Game
{
private:
	GraphicsManager graphicsManager;

	Player* player1;

	Phase phase1;

	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

public:
	Game();
	~Game();

	void createMap();
	void initPlayers();
	void initEnemies();

	void update();
	void updateSFMLEvents();
	void updateDeltaTime();
	void updateCollision();

	void render();

	void execute();
};

