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
	if (id == SKELETON) {
		Skeleton* tmp = nullptr;
		tmp = new Skeleton(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, SKELETON_SPEED, SKELETON_HP);
		tmp->setPlayer(this->player);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == ARCHER) {
		Archer* tmp = nullptr;
		tmp = new Archer(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, SKELETON_SPEED, SKELETON_HP);
		tmp->setPlayer(this->player);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == FIRE) {
		Fire* tmp = nullptr;
		tmp = new Fire(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == TELEPORT) {
		Teleport* tmp = nullptr;
		tmp = new Teleport(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == SLOW) {
		Slow* tmp = nullptr;
		tmp = new Slow(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	// PLATAFORMA
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
		if (this->entityList[i]->getId() == SKELETON || this->entityList[i]->getId() == PLAYER || this->entityList[i]->getId() == ARCHER)
			if (static_cast<Character*>(this->entityList[i])->isDead())
				this->entityList.pop(this->entityList[i]);
	}
}

void Phase::render()
{
	int fromX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) - 10;
	int toX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) + 10;
	int fromY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) - 10;
	int toY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) + 10;

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
		this->entityList[i]->renderShape();
		if (this->entityList[i]->getId() == ARCHER) {
			Archer* tmp = static_cast<Archer*>(this->entityList[i]);
			for (int j = 0; j < tmp->getArrowsVector()->size(); j++)
				if (tmp->getArrowsVector()->size() > 0)
					this->graphicsManager->renderShape(tmp->getArrowsVector()->operator[](j)->getShape());
		}

	}

	if (this->player->getSwordHitbox())
		this->player->renderSwordHitBox_TMP();

	for (int i = fromY; i < toY; i++)
		for (int j = fromX; j < toX; j++)
			if (this->platformList[i][j].getId() != BACKGROUND) {
				this->platformList[i][j].renderSprite();
				this->platformList[i][j].renderShape();
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
