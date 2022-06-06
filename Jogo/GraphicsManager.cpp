#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game TecProg");
	this->view.setSize(1280.f, 720.f);
}

GraphicsManager::~GraphicsManager()
{

	/* INSPIRADO NO TUTORIAL DO MONITOR MATHEUS BURDA */

	/* Desaloca as texturas */
	std::map<std::string, sf::Texture*>::iterator it;
	for (it = this->textures.begin(); it != this->textures.end(); ++it)
		delete it->second;

	// Deleta a janela
	delete (this->window);
}

// Carrega as texturas e inserem elas no mapa de texturas (caso ainda não tenham sido criadas)
sf::Texture* GraphicsManager::loadTextures(std::string pathToTexture, std::string textureName)
{
	/* Tenta encontrar a textura no mapa de texturas a partir da string textureName */
	std::map<std::string, sf::Texture*>::iterator it;
	for (it = this->textures.begin(); it != this->textures.end(); ++it)
		if (it->first == textureName)
			return it->second;

	/* Caso a textura ainda não exista no mapa, cria ela e insere no mapa */

	sf::Texture* tmp = new sf::Texture();

	if (!tmp->loadFromFile(pathToTexture))
		throw "ERROR::LOAD_TEXTURES::COULD_NOT_LOAD_FROM_FILE";

	this->textures.insert(std::pair<std::string, sf::Texture*>(textureName, tmp));

	return tmp;
}

void GraphicsManager::resetView()
{
	this->view.setCenter(sf::Vector2f(1280.f / 2, 720.f / 2));
	this->setView();
}

void GraphicsManager::resizeView()
{
	float aspectRatio = (float)this->window->getSize().x / (float)this->window->getSize().y;
	this->view.setSize(1280.f * aspectRatio, 720.f * aspectRatio);
}
