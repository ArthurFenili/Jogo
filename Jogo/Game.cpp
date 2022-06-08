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

// Verifica constantemente v�rias a��es que s�o necess�rias para o bom funcionamento da aplica��o
void Game::update()
{
	this->updateSFMLEvents();
	if (!this->states.empty()) {
		this->states.top()->update(dt);
	}
	
}

// Verifica se o usu�rio pediu para fechar a janela
void Game::updateSFMLEvents()
{
	while (this->graphicsManager.pollEvent(&this->sfEvent)) {
		if (this->sfEvent.type == sf::Event::Closed)
			this->graphicsManager.closeWindow();
		if (this->sfEvent.type == sf::Event::Resized)
			this->graphicsManager.resizeView();
	}
}

// Calcula o Delta Time constantemente
void Game::updateDeltaTime()
{
	this->dt = this->dtClock.restart().asSeconds();

	/* Conserta um bug no qual se voc� arrastar a janela com o mouse, o player muda de posi��o */
	if (this->dt > 1.f / 20.f)
		this->dt = 1.f / 20.f;
}

void Game::render()
{
	//this->graphicsManager.clearWindow();  // Limpa a janela

	if (!this->states.empty()) {
		this->states.top()->render();
	}

	this->graphicsManager.displayWindow();  // Imprime todos os objetos que foram renderizados na janela}
}

void Game::execute()
{
	while (this->graphicsManager.isWindowOpen()) {
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}