#include "ForestPhase.h"

ForestPhase::ForestPhase(GraphicsManager* graphicsManager, float* dt, int id) :
	Phase(graphicsManager, dt, id)
{
	this->collisionsManager = CollisionsManager(this);
}

ForestPhase::ForestPhase()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
	this->platformList = nullptr;
}

ForestPhase::~ForestPhase()
{
	this->player1 = nullptr;
	this->player2 = nullptr;
}

void ForestPhase::loadMap(std::string pathToTilemap)
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
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile0_p1.png", "TILE_0_P1");
				else if (map[i][j].x == 1 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile1_p1.png", "TILE_1_P1");
				else if (map[i][j].x == 2 && map[i][j].y == 0)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile2_p1.png", "TILE_2_P1");
				else if (map[i][j].x == 0 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(CASTLE, 3.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f * 2.f), "images/castle.png", "CASTLE");
				else if (map[i][j].x == 1 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile3_p1.png", "TILE_3_P1");
				else if (map[i][j].x == 2 && map[i][j].y == 1)
					this->platformList[i][j] = this->createEntity(BLOCK, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "images/tile4_p1.png", "TILE_4_P1");
			}
			else
				this->platformList[i][j] = this->createEntity(BACKGROUND, 1.f, sf::Vector2f((float)j * 64.f, (float)i * 64.f), sf::Vector2f(64.f, 64.f), "", "BACKGROUND");
		}
	}
}
