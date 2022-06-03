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

	this->entityList.addEntity(tmp);
}

void Phase::loadMap(std::string mapFileName)
{
	std::ifstream mapFile;
	mapFile.open(mapFileName, std::ifstream::in);

	std::vector<std::vector<sf::Vector2i>> map;
	std::vector<sf::Vector2i> tmpMap;
	
	sf::Texture* tileTexture = this->graphicsManager->loadTextures("images/tileMap.png", "TILEMAP");
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
					this->setPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/block.png", "BLOCK", sf::Vector2f(64.f, 64.f));
				else if (map [i][j].x == 0 && map[i][j].y == 1)
					this->setPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/teleport.png", "TELEPORT", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 1 && map[i][j].y == 0)
					this->setPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/slow.png", "SLOW", sf::Vector2f(64.f, 64.f));
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->setPlatform(sf::Vector2f((float)j * 64.f, (float)i * 64.f), "images/fire.png", "FIRE", sf::Vector2f(64.f, 64.f));
			}
		}
	}
}

void Phase::update()
{
	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->update();
		if (static_cast<Character*>(this->entityList[i])->isDead())
			this->entityList.pop(this->entityList[i]);
	}
}

void Phase::render()
{
	for (int i = 0; i < this->platformList.getSize(); i++)
		this->platformList[i]->renderShape();

	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->renderShape();
		this->entityList[i]->renderSprite();
	}
		
}
