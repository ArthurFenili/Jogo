#pragma once

#include "GraphicsManager.h"

enum types {
	FOREST_PHASE = 0, CASTLE_PHASE = 1, FIRE = 2, TELEPORT = 3, SLOW = 4, BLOCK = 5, DOOR = 6, CASTLE = 7, BACKGROUND = 8, PLAYER = 9, SWORD = 10, SKELETON = 11, ARCHER = 12, STATE = 13, DARKKNIGHT = 14
};

class Ent
{
protected:
	GraphicsManager* graphicsManager;
	float* dt;

	int id;

public:
	Ent(GraphicsManager* graphicsManager, float* dt, int id);
	Ent();
	~Ent();

	int getId() { return this->id; }
};