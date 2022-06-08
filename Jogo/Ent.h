#pragma once

#include "GraphicsManager.h"

class Ent
{
protected:
	GraphicsManager* graphicsManager;
	float* dt;

	int id;

	enum types {
		FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, ENEMY = 9, PLAYER = 10, SWORD = 11
	};

public:
	Ent(GraphicsManager* graphicsManager, float* dt, int id);
	Ent();
	~Ent();

	int getId() { return this->id; }
};
