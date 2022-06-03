#include "Phase.h"
#include "EnemyProjectile.h"

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

void Phase::setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize)
{
	Platform* tmp = nullptr;
	tmp = new Platform(this->graphicsManager, position, pathToTexture, textureName, bodySize);

	this->platformList.addPlatform(tmp);
}

void Phase::setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player)
{
	Enemy* tmp = nullptr;
	tmp = new Enemy(this->graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed);
	tmp->setPlayer(player);

	this->entitiesList.addEntity(tmp);
}

void Phase::setEnemy2(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player)
{
	EnemyProjectile* tmp = nullptr;
	tmp = new EnemyProjectile(this->graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed);
	tmp->setPlayer(player);

	this->entitiesList.addEntity(tmp);
}

void Phase::update()
{
	for (int i = 0; i < this->entitiesList.getSize(); i++) {
		this->entitiesList[i]->update();
		if (static_cast<Character*>(this->entitiesList[i])->isDead())
			this->entitiesList.removeEntity(this->entitiesList[i]);
	}
}

void Phase::render()
{
	for (int i = 0; i < this->entitiesList.getSize(); i++) {
		this->entitiesList[i]->renderShape();
		this->entitiesList[i]->renderSprite();	

		if (i != 0) { // arrumar esse if pq se ativar os skeleton vai parar de funcionar pq vai tentar pegar projetil de skeleton
					// talvez com um dynamic cast (??)
			EnemyProjectile* tmp = static_cast<EnemyProjectile*>(this->entitiesList[i]);
			for (int j = 0; j < tmp->getVectorProjectiles()->size(); j++) { 
				if (tmp->getVectorProjectiles()->size() > 0) {
					this->graphicsManager->renderShape(tmp->getVectorProjectiles()->operator[](j));
				}
			}
		}
	}


	for (int i = 0; i < this->platformList.getSize(); i++) {
		this->platformList[i]->renderShape();
	}
}
