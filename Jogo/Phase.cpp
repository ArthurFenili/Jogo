#include "Phase.h"

const float SKELETON_SPEED = 30.f;
const int SKELETON_HP = 500;

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

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j].x != -1 && map[i][j].y != -1) {	
				if (map[i][j].x == 0 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile0.png", "TILE_0");
				else if (map[i][j].x == 1 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile1.png", "TILE_1");
				else if (map[i][j].x == 2 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile2.png", "TILE_2");
				else if (map[i][j].x == 0 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(DOOR, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/door.png", "DOOR");
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile3.png", "TILE_3");
				else if (map[i][j].x == 2 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile4.png", "TILE_4");
			}
			else
				this->platformList[i][j] = this->createEntity(BACKGROUND, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/no_collider.png", "BACKGROUND");	
		}
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
	int fromX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) - 7;
	int toX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) + 7;
	int fromY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) - 7;
	int toY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) + 7;

	if (fromX < 0)
		fromX = 0;
	else if (toX >= 50)
		toX = 49;

	if (fromY < 0)
		fromY = 0;
	else if (toY >= 30)
		toY = 29;

	for (int i = fromY; i < toY; i++)
		for (int j = fromX; j < toX; j++)
			if (this->platformList[i][j].getId() != BACKGROUND)
				this->platformList[i][j].renderSprite();
				
	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->renderSprite();
		this->entityList[i]->renderShape();
	}
}

void Phase::clearPlatformList()
{
	for (int i = 0; i < 30; i++)
		delete[] this->platformList[i];
	delete this->platformList;
}
