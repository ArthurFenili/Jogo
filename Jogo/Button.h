#pragma once

#include <SFML/Graphics.hpp>

enum buttonStates {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_PRESSED
};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font* font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text, 
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	bool isPressed();
	sf::RectangleShape* getShape() { return &this->shape; }
	sf::Text* getText() { return &this->text; }

	void update(sf::Vector2f mousePos);
};

