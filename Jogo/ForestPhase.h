#pragma once

#include "Phase.h"

class ForestPhase : public Phase
{
private:

public:
	ForestPhase(GraphicsManager* graphicsManager, float* dt, int id);
	ForestPhase();
	~ForestPhase();
};
