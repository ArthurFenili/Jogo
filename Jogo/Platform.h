#pragma once

#include "Entity.h"

class Platform : public Entity
{
private:

public:
	Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	~Platform();
};
