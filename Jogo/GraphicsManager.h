#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class GraphicsManager
{
private:
	sf::RenderWindow* window;
	sf::View view;
	std::map<std::string, sf::Texture*> textures;

public:
	GraphicsManager();
	~GraphicsManager();

	sf::Texture* loadTextures(std::string pathToTexture, std::string textureName);

	void resizeView();

	void clearWindow(int phase);

	void resetView();

	void setViewSize(sf::Vector2f size) { this->view.setSize(size); }

	bool pollEvent(sf::Event* sfEvent) { return this->window->pollEvent(*sfEvent); }

	bool isWindowOpen() { return this->window->isOpen(); }

	void displayWindow() { this->window->display(); }

	void closeWindow() { this->window->close(); }

	void updateView(sf::RectangleShape* body) { this->view.setCenter(body->getPosition()); }

	void setView() { this->window->setView(this->view); }

	sf::View getView() { return this->view; }

	void renderShape(sf::RectangleShape* shape) { this->window->draw(*shape); }
	void renderSprite(sf::Sprite* sprite) { this->window->draw(*sprite); }
	void renderText(sf::Text* text) { this->window->draw(*text); }

	sf::RenderWindow* getWindow() { return window; }
};