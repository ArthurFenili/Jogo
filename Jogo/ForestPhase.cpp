#include "ForestPhase.h"

ForestPhase::ForestPhase(GraphicsManager* graphicsManager, float* dt, int id) :
	Phase(graphicsManager, dt, id)
{
	this->collisionsManager = CollisionsManager();

	this->texturePaths.push_back("images/tile0_p1.png");
	this->texturePaths.push_back("images/tile1_p1.png");
	this->texturePaths.push_back("images/tile2_p1.png");
	this->texturePaths.push_back("images/castle.png");
	this->texturePaths.push_back("images/tile3_p1.png");
	this->texturePaths.push_back("images/tile4_p1.png");
	this->texturePaths.push_back("");

	this->textureNames.push_back("TILE_0_P1");
	this->textureNames.push_back("TILE_1_P1");
	this->textureNames.push_back("TILE_2_P1");
	this->textureNames.push_back("CASTLE");
	this->textureNames.push_back("TILE_3_P1");
	this->textureNames.push_back("TILE_4_P1");
	this->textureNames.push_back("BACKGROUND");
}

ForestPhase::ForestPhase() :
	Phase()
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
