#pragma once
#include <iostream>
#include "State.h"
#include <SFML/Graphics.hpp>

class InputManager
{
private:
	sf::Event ev;
	bool saved;
	std::string strtmp;
public:
	InputManager();
	~InputManager();

	std::string readString(GraphicsManager* graphicsManager);
};