#include "Phase.h"

Phase::Phase(GraphicsManager* graphicsManager)
{
	this->graphicsManager = graphicsManager;
}

Phase::Phase()
{
	this->graphicsManager = nullptr;
}

Phase::~Phase()
{
}

// Cria um objeto da classe Platform e insere ele na lista
void Phase::setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize)
{
	Platform* tmp = nullptr;
	tmp = new Platform(this->graphicsManager, position, pathToTexture, textureName, bodySize);

	this->platformList.addPlatform(tmp);
}

void Phase::renderShape(int index)
{
	this->graphicsManager->renderShape(this->platformList[index]->getShape());
}
