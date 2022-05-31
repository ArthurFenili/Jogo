#pragma once

#include "PlatformList.h"

class Phase
{
private:
	GraphicsManager* graphicsManager;
	PlatformList platformList;

public:
	Phase(GraphicsManager* graphicsManager);
	Phase();
	~Phase();

	void setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);

	PlatformList* getPlatformList() { return &this->platformList; }

	void renderShape(int index);
};
