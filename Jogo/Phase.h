#pragma once

#include "EntityList.h"
#include "PlatformList.h"
#include "Enemy.h"

class Phase
{
private:
	GraphicsManager* graphicsManager;
	EntityList entityList;
	PlatformList platformList;

public:
	Phase(GraphicsManager* graphicsManager);
	Phase();
	~Phase();

	void setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	void setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player);

	void addEntity(Entity* entity) { this->entityList.addEntity(entity); }

	void update();

	void render();

	EntityList* getEntityList() { return &this->entityList; }
	PlatformList* getPlatformList() { return &this->platformList; }
};
