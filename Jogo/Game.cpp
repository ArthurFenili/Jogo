#include "Game.h"

Game::Game()
{
	this->initStates();

	execute();
}

Game::~Game()
{
}

void Game::initStates()
{
	State* mainMenu = new MainMenuState(&this->graphicsManager, &this->states, &this->dt);
	this->states.push(mainMenu);
}

void Game::execute()
{
	while (this->graphicsManager.isWindowOpen()) {
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}

// Calcula o Delta Time constantemente
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();

	/* Conserta um bug no qual se você arrastar a janela com o mouse, o player muda de posição */
	if (this->dt > 1.f / 20.f)
		this->dt = 1.f / 20.f;
}

// Faz o update da state atual do jogo
void Game::update()
{
	this->updateSFMLEvents();
	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
	}

}

// Verifica se o usuário pediu para fechar a janela ou redimensinou a janela da aplicação
void Game::updateSFMLEvents()
{
	while (this->graphicsManager.pollEvent(&this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->graphicsManager.closeWindow();
		if (this->sfEvent.type == sf::Event::Resized)
			this->graphicsManager.resizeView();
	}
}

// Imprime os objetos da state atual na tela
void Game::render()
{
	if (!this->states.empty())
		this->states.top()->render();

	this->graphicsManager.displayWindow(); 
}
 