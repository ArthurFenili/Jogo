#pragma once

#include "EntityList.h"
#include "Enemy.h"
#include "Obstacle.h"
#include <fstream>
#include <sstream>

class Phase : public Ent
{
protected:
	Player* player;

	EntityList entityList;
	Entity** platformList;

public:
	Phase(GraphicsManager* graphicsManager, float* dt, int id);
	Phase();
	~Phase();

	Entity createEntity(int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName);

	void addEntity(Entity* entity) { this->entityList.addEntity(entity); }

	void setPlayer(Player* player) { this->player = player; }
	Player* getPlayer() { return this->player; }

	void loadMap(std::string pathToTilemap);

	void update();

	void render();

	EntityList* getEntityList() { return &this->entityList; }
	Entity** getPlatformList() { return this->platformList; }

	void clearPlatformList();
};
