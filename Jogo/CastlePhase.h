#pragma once

#include "Phase.h"

class CastlePhase : public Phase
{
private:

public:
	CastlePhase(GraphicsManager* graphicsManager, float* dt, int id);
	CastlePhase();
	~CastlePhase();
};

