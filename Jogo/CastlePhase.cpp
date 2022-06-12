#include "CastlePhase.h"

CastlePhase::CastlePhase(GraphicsManager* graphicsManager, float* dt, int id) :
	Phase(graphicsManager, dt, id)
{
	this->collisionsManager = CollisionsManager();

	this->texturePaths.push_back("images/tile0.png");
	this->texturePaths.push_back("images/tile1.png");
	this->texturePaths.push_back("images/tile2.png");
	this->texturePaths.push_back("images/door.png");
	this->texturePaths.push_back("images/tile3.png");
	this->texturePaths.push_back("images/tile4.png");
	this->texturePaths.push_back("");

	this->textureNames.push_back("TILE_0");
	this->textureNames.push_back("TILE_1");
	this->textureNames.push_back("TILE_2");
	this->textureNames.push_back("DOOR");
	this->textureNames.push_back("TILE_3");
	this->textureNames.push_back("TILE_4");
	this->textureNames.push_back("BACKGROUND");
}

CastlePhase::CastlePhase() :
	Phase()
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
