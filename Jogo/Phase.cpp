#include "Phase.h"

const float SKELETON_SPEED = 30.f;
const long int SKELETON_HP = 125000;

Phase::Phase(GraphicsManager* graphicsManager, float* dt, int id) :
	Ent(graphicsManager, dt, id)
{
	this->player = nullptr;

	this->platformList = new Entity * [30];
	for (int i = 0; i < 30; i++)
		this->platformList[i] = new Entity[50];
}

Phase::Phase() :
	Ent()
{
	this->player = nullptr;
	this->platformList = nullptr;
}

Phase::~Phase()
{
	this->player = nullptr;
}

Entity Phase::createEntity(int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName)
{
	if (id == ENEMY) {
		Enemy* tmp = nullptr;
		tmp = new Enemy(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, SKELETON_SPEED, SKELETON_HP);
		static_cast<Enemy*>(tmp)->setPlayer(this->player);
		this->entityList.addEntity(tmp);
		return *tmp;
	}
	else if (id == FIRE || id == TELEPORT || id == SLOW) {
		Obstacle* tmp = nullptr;
		tmp = new Obstacle(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else {
		Entity* tmp = nullptr;
		tmp = new Entity(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName);
		return *tmp;
	}
}

void Phase::update()
{
	for (int i = 0; i < this->entityList.getSize(); i++) {
		if (this->entityList[i]->getId() != SLOW)
			this->entityList[i]->update();
		if (this->entityList[i]->getId() == ENEMY || this->entityList[i]->getId() == PLAYER)
			if (static_cast<Character*>(this->entityList[i])->isDead())
				this->entityList.pop(this->entityList[i]);
	}
}

void Phase::render()
{
	int fromX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) - 12;
	int toX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) + 12;
	int fromY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) - 12;
	int toY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) + 12;

	if (fromX < 0)
		fromX = 0;
	else if (toX >= 50)
		toX = 49;

	if (fromY < 0)
		fromY = 0;
	else if (toY >= 30)
		toY = 29;

	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->renderSprite();
		//this->entityList[i]->renderShape();
	}

	//if (this->player->getSwordHitbox())
		//this->player->renderSwordHitBox_TMP();

	for (int i = fromY; i < toY; i++)
		for (int j = fromX; j < toX; j++)
			if (this->platformList[i][j].getId() != BACKGROUND) {
				this->platformList[i][j].renderSprite();
				//this->platformList[i][j].renderShape();
			}
}

void Phase::clearPlatformList()
{
	for (int i = 0; i < 30; i++)
		delete[] this->platformList[i];
	delete this->platformList;
}

void Phase::clearEntityList()
{
	this->entityList.clearList();
}
