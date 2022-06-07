#include "Phase.h"
#include "EnemyProjectile.h"

Phase::Phase(GraphicsManager* graphicsManager, int* score)
{
	this->graphicsManager = graphicsManager;
	this->score = score;
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

void Phase::setEnemy3(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player)
{
	Boss* tmp = nullptr;
	tmp = new Boss(this->graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed);
	tmp->setPlayer(player);

	this->entitiesList.addEntity(tmp);
}

void Phase::update()
{
	for (int i = 0; i < this->entitiesList.getSize(); i++) {
		this->entitiesList[i]->update();
		if (static_cast<Character*>(this->entitiesList[i])->isDead()) {
			this->entitiesList.removeEntity(this->entitiesList[i]);
			(*this->score += 100);
		}
	}
}

void Phase::render()
{
	for (int i = 0; i < this->entitiesList.getSize(); i++) {
		this->entitiesList[i]->renderShape();
		this->entitiesList[i]->renderSprite();	

		if (dynamic_cast<EnemyProjectile*>(this->entitiesList[i]) != nullptr) {
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
