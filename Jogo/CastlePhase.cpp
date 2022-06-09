#include "CastlePhase.h"

CastlePhase::CastlePhase(GraphicsManager* graphicsManager, float* dt, int id) :
	Phase(graphicsManager, dt, id)
{
	this->collisionsManager = CollisionsManager(this);
}

CastlePhase::CastlePhase()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
	this->platformList = nullptr;
}

CastlePhase::~CastlePhase()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
}

void CastlePhase::loadMap(std::string pathToTilemap)
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
					this->platformList[i][j] = this->createEntity(DOOR, 2.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f * 2.f), "images/door.png", "DOOR");
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile3.png", "TILE_3");
				else if (map[i][j].x == 2 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile4.png", "TILE_4");
			}
			else
				this->platformList[i][j] = this->createEntity(BACKGROUND, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "", "BACKGROUND");
		}
	}
}

