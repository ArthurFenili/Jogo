#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"

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