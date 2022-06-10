#pragma once

#include "Collider.h"

class Phase;

class CollisionsManager
{
private:
	Phase* phase;

	enum types {
		FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, PLAYER = 9, SWORD = 10, SKELETON = 11, ARCHER = 12
	};

public:
	CollisionsManager(Phase* phase = nullptr);
	~CollisionsManager();

	void updateCollision();
};
