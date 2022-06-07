#pragma once

#include "GraphicsManager.h"

class Ent
{
protected:
	GraphicsManager* graphicsManager;
	float* dt;

	int id;

	enum types {
		PHASE = 0, FIRE = 1, TELEPORT = 2, SLOW = 3, BLOCK = 4, DOOR = 5, BACKGROUND = 6, ENEMY = 7, PLAYER = 8, SWORD = 9
	};

public:
	Ent(GraphicsManager* graphicsManager, float* dt, int id);
	Ent();
	~Ent();

	int getId() { return this->id; }
};
