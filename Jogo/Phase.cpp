#include "Phase.h"

Phase::Phase(GraphicsManager* graphicsManager, float* dt)
{
	this->graphicsManager = graphicsManager;
	this->dt = dt;

	this->platformList2 = new Platform* [30];
	for (int i = 0; i < 30; i++)
		this->platformList2[i] = new Platform[50];
}

Phase::Phase()
{
	this->graphicsManager = nullptr;
	this->dt = nullptr;
	this->platformList2 = nullptr;
}

Phase::~Phase()
{
}

Platform Phase::createPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float spriteScale)
{
	Platform* tmp = nullptr;
	tmp = new Platform(this->graphicsManager, position, pathToTexture, textureName, bodySize, this->dt, spriteScale);

	return *tmp;
}

void Phase::setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player)
{
	Enemy* tmp = nullptr;
	tmp = new Enemy(this->graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed);
	tmp->setPlayer(player);

	this->entityList.addEntity(tmp);
}

void Phase::loadMap(std::string mapFileName)
{
	std::ifstream mapFile;
	mapFile.open(mapFileName, std::ifstream::in);

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpMap;
	
	sf::Texture* tileTexture = this->graphicsManager->loadTextures("images/tileMap2.png", "TILEMAP");
	sf::RectangleShape tiles;

	tiles.setTexture(tileTexture);

	if (mapFile.is_open()) {
		while (!mapFile.eof()) {
			std::string string, value;
			std::getline(mapFile, string);
			std::stringstream stream(string);

			while (std::getline(stream, value, ' ')) {
				std::string xx = value.substr(0, value.find(','));
				std::string yy = value.substr(value.find(',') + 1);

				int x, y, i, j;
				for (i = 0; i < xx.length(); i++) {
					if (!isdigit(xx[i]))
						break;
				}
				for (j = 0; j < yy.length(); j++) {
					if (!isdigit(yy[j]))
						break;
				}
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
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile0.png", "TILE_0", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 1 && map[i][j].y == 0)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile1.png", "SLOW", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 2 && map[i][j].y == 0)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile2.png", "TILE_2", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 3 && map[i][j].y == 0)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile3.png", "TILE_3", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 4 && map[i][j].y == 0)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile4.png", "TILE_4", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 0 && map[i][j].y == 1)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/portal.png", "TELEPORT", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/fire.png", "FIRE", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 2 && map[i][j].y == 1)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/door.png", "DOOR", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 3 && map[i][j].y == 1)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/tile5.png", "TILE_5", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 4 && map[i][j].y == 1)
					this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/window.png", "WINDOW", sf::Vector2f(64.f, 64.f));
			}
			else {
				this->platformList2[i][j] = this->createPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/no_collider.png", "NO_COLLIDER", sf::Vector2f(64.f, 64.f));
			}
		}
	}
}

void Phase::update()
{
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 50; j++)
			if (this->platformList2[i][j].getObstacleType() == 1 || this->platformList2[i][j].getObstacleType() == 3)
				this->platformList2[i][j].updateAnimation();

	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->update();
		if (static_cast<Character*>(this->entityList[i])->isDead())
			this->entityList.pop(this->entityList[i]);
	}
}

void Phase::render()
{

	int fromX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) - 15;
	int toX = (int)(this->graphicsManager->getView().getCenter().x / 64.f) + 15;
	int fromY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) - 15;
	int toY = (int)(this->graphicsManager->getView().getCenter().y / 64.f) + 15;

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
			if (this->platformList2[i][j].getObstacleType() != 6)
				this->platformList2[i][j].renderShape();

	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->renderShape();
		this->entityList[i]->renderSprite();
	}
}
