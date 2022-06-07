#include "GraphicsManager.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const float VIEW_SIZE = 512.f;

GraphicsManager::GraphicsManager()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 64), "Game TecProg");
	this->view.setSize(VIEW_SIZE, VIEW_SIZE);
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

	if (textureName == "NONE" || textureName == "BACKGROUND")
		return nullptr;

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

void GraphicsManager::resizeView()
{
	float aspectRatio = (float)this->window->getSize().x / (float)this->window->getSize().y;
	this->view.setSize(VIEW_SIZE * aspectRatio, VIEW_SIZE);
}
