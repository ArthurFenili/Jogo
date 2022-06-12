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

// Verifica constantemente várias ações que são necessárias para o bom funcionamento da aplicação
void Game::update()
{
	this->updateSFMLEvents();
	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
	}

}

// Verifica se o usuário pediu para fechar a janela
void Game::updateSFMLEvents()
{
	while (this->graphicsManager.pollEvent(&this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->graphicsManager.closeWindow();
		if (this->sfEvent.type == sf::Event::Resized)
			this->graphicsManager.resizeView();
	}
}

void Game::render()
{
	if (!this->states.empty())
		this->states.top()->render();

	this->graphicsManager.displayWindow();  // Imprime todos os objetos que foram renderizados na janela}
}
 