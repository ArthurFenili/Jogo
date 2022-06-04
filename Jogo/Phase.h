#pragma once

#include "EntityList.h"
#include "Platform.h"
#include "Enemy.h"
#include <fstream>
#include <sstream>

class Phase
{
private:
	GraphicsManager* graphicsManager;
	EntityList entityList;

	Platform** platformList2;

	float* dt;

public:
	Phase(GraphicsManager* graphicsManager, float* dt);
	Phase();
	~Phase();

	Platform createPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float spriteScale = 1.f);
	void setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player);

	void addEntity(Entity* entity) { this->entityList.addEntity(entity); }

	void loadMap(std::string mapFileName);

	void update();

	void render();

	EntityList* getEntityList() { return &this->entityList; }
	Platform** getPlatformList() { return this->platformList2; }
};
