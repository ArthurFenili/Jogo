#pragma once

#include "Collider.h"
#include "EntityList.h"
#include "Player.h"
class Phase;

class CollisionsManager
{
private:
	Player* player1;
	Player* player2;
	EntityList* entityList;
	Entity** platformlist;

	enum types {
		FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, PLAYER = 9, SWORD = 10, SKELETON = 11, ARCHER = 12
	};

public:
	CollisionsManager(EntityList* entityList, Entity** platformList);
	CollisionsManager() {}
	~CollisionsManager();

	void updateCollision();

	void setPlayer1(Player* player) { this->player1 = player; }
	void setPlayer2(Player* player) { this->player2 = player; }
};
