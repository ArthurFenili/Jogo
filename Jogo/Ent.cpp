#include "Ent.h"

Ent::Ent(GraphicsManager* graphicsManager, float* dt, int id)
{
	this->graphicsManager = graphicsManager;
	this->dt = dt;
	this->id = id;
}

Ent::Ent()
{
	this->graphicsManager = nullptr;
	this->dt = nullptr;
	this->id = -1;
}

Ent::~Ent()
{
	this->graphicsManager = nullptr;
	this->dt = nullptr;
}
