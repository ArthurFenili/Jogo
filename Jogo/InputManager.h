#pragma once
#include <iostream>
#include "State.h"
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager();
	~InputManager();

	std::string readString(GraphicsManager* graphicsManager);
};

