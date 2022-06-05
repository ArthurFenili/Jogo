#include "MainMenuState.h"

MainMenuState::MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	std::cout << "MainMenuState" << std::endl;

	this->dt = dt;

	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));
	this->background.setOrigin(sf::Vector2f(0.f, 0.f));
	this->background.setFillColor(sf::Color::Green);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
		State* newGame = new NewGameState(this->graphicsManager, this->states, this->dt);
		this->states->push(newGame);
	}
}

void MainMenuState::update(float dt)
{
	this->updateInput();
}

void MainMenuState::render()
{
	this->graphicsManager->renderShape(&background);
}

void MainMenuState::resetState()
{
}
