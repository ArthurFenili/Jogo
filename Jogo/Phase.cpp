#include "Phase.h"
#include "PlayingState.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;

const float SKELETON_SPEED = 30.f;
const int SKELETON_HP = 150;

const float ARCHER_SPEED = 15.f;
const int ARCHER_HP = 200;

const float DARK_KNIGHT_SPEED = 10.f;
const int DARK_KNIGHT_HP = 1000;

Phase::Phase(GraphicsManager* graphicsManager, float* dt, int id) :
	Ent(graphicsManager, dt, id)
{
	this->player1 = nullptr;
	this->player2 = nullptr;

	this->collisionsManager = CollisionsManager();

	this->platformList = new Entity * [MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++)
		this->platformList[i] = new Entity[MAP_WIDTH];
}

Phase::Phase() :
	Ent()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
	this->platformList = nullptr;
}

Phase::~Phase()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
}

void Phase::loadMap(std::string pathToTilemap)
{
	std::ifstream mapFile;
	mapFile.open(pathToTilemap, std::ifstream::in);

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpMap;

	if (mapFile.is_open()) {
		while (!mapFile.eof()) {
			std::string string, value;
			std::getline(mapFile, string);
			std::stringstream stream(string);
			while (std::getline(stream, value, ' ')) {
				std::string xx = value.substr(0, value.find(','));
				std::string yy = value.substr(value.find(',') + 1);

				int x, y, i, j;

				for (i = 0; i < xx.length(); i++)
					if (!isdigit(xx[i]))
						break;

				for (j = 0; j < yy.length(); j++)
					if (!isdigit(yy[j]))
						break;
				x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
				y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

				tmpMap.push_back(sf::Vector2i(x, y));
			}
			map.push_back(tmpMap);
			tmpMap.clear();
		}
	}
	mapFile.close();

	int phaseEnd = PlayingState::forestPhase ? static_cast<int>(CASTLE) : static_cast<int>(DOOR);

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].x != -1 && map[i][j].y != -1) {
				if (map[i][j].x == 0 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[0], this->textureNames[0]);
				else if (map[i][j].x == 1 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[1], this->textureNames[1]);
				else if (map[i][j].x == 2 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[2], this->textureNames[2]);
				else if (map[i][j].x == 0 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(phaseEnd, 2.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f * 2.f), this->texturePaths[3], this->textureNames[3]);
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[4], this->textureNames[4]);
				else if (map[i][j].x == 2 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[5], this->textureNames[5]);
			}
			else
				this->platformList[i][j] = this->createEntity(BACKGROUND, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), this->texturePaths[6], this->textureNames[6]);
		}
	}
}

Entity Phase::createEntity(int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName)
{
	if (id == SKELETON) {
		Skeleton* tmp = nullptr;
		tmp = new Skeleton(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, SKELETON_SPEED, SKELETON_HP);
		tmp->setPlayer(this->player1);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == ARCHER) {
		Archer* tmp = nullptr;
		tmp = new Archer(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, ARCHER_SPEED, ARCHER_HP);
		tmp->setPlayer(this->player1);
		this->entityList.addEntity(tmp);
		return *tmp;
	}

	else if (id == DARKKNIGHT) {
		DarkKnight* tmp = nullptr;
		tmp = new DarkKnight(this->graphicsManager, this->dt, id, spriteScale, position, bodySize, pathToTexture, textureName, DARK_KNIGHT_SPEED, DARK_KNIGHT_HP);
		tmp->setPlayer(this->player1);
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

		if (this->entityList[i]->getId() == SKELETON || this->entityList[i]->getId() == ARCHER || this->entityList[i]->getId() == DARKKNIGHT) {
			if (static_cast<Character*>(this->entityList[i])->isDead()) {
				this->entityList.pop(this->entityList[i]);
				if (dynamic_cast<Skeleton*>(this->entityList[i]) != nullptr)
					PlayingState::score += 100;
				else if (dynamic_cast<Archer*>(this->entityList[i]) != nullptr)
					PlayingState::score += 150;
			}
		}

		if (this->entityList[i]->getId() == PLAYER)
			if (static_cast<Character*>(this->entityList[i])->isDead())
				this->entityList.pop(this->entityList[i]);
	}

	this->collisionsManager.updateCollision();
}

void Phase::render()
{
	int fromX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) - 10;
	int toX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) + 10;
	int fromY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) - 10;
	int toY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) + 10;

	if (fromX < 0)
		fromX = 0;
	else if (toX >= MAP_WIDTH)
		toX = 29;

	if (fromY < 0)
		fromY = 0;
	else if (toY >= MAP_HEIGHT)
		toY = 19;

	int numPlayers = PlayingState::twoPlayers ? 2 : 1;

	for (int i = 0; i < this->entityList.getSize() - numPlayers; i++) {

		this->entityList[i]->renderSprite();

		if (this->entityList[i]->getId() == ARCHER)
			for (int j = 0; j < static_cast<Archer*>(this->entityList[i])->getArrowsVector()->size(); j++)
				this->graphicsManager->renderShape(static_cast<Archer*>(this->entityList[i])->getArrowsVector()->operator[](j)->getShape());
	}

	for (int i = fromY; i < toY; i++)
		for (int j = fromX; j < toX; j++)
			if (this->platformList[i][j].getId() != BACKGROUND)
				this->platformList[i][j].renderSprite();

	if (numPlayers > 1)
		this->entityList[this->entityList.getSize() - 2]->renderSprite();
	if (numPlayers >= 1)
		this->entityList[this->entityList.getSize() - 1]->renderSprite();
}

void Phase::clearPlatformList()
{
	for (int i = 0; i < 20; i++)
		delete[] this->platformList[i];
	delete this->platformList;
}

void Phase::clearEntityList()
{
	this->entityList.clearList();
}

void Phase::initCollisionsManager()
{
	this->collisionsManager = CollisionsManager(&this->entityList, this->platformList, this->player1, this->player2);
}