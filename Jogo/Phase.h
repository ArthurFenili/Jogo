#pragma once

#include <fstream>
#include <sstream>
#include "EntityList.h"
#include "Archer.h"
#include "Skeleton.h"
#include "Fire.h"
#include "Teleport.h"
#include "Slow.h"

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

	virtual void loadMap(std::string pathToTilemap) {}

	void update();

	void render();

	void clearPlatformList();
	void clearEntityList();

	void addEntity(Entity* entity) { this->entityList.addEntity(entity); }

	void setPlayer(Player* player) { this->player = player; }
	Player* getPlayer() { return this->player; }

	EntityList* getEntityList() { return &this->entityList; }
	Entity** getPlatformList() { return this->platformList; }
};
