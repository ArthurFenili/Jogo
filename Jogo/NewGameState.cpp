#include "NewGameState.h"

NewGameState::NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt):
	State(graphicsManager, states, dt)
{
	std::cout << "NewGameState" << std::endl;

	this->dt = dt;
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));
	this->background.setOrigin(sf::Vector2f(0.f, 0.f));
	this->background.setFillColor(sf::Color::Red);
}

NewGameState::~NewGameState()
{
}

void NewGameState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
		this->removeCurrentState();
		this->updateStateChange();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}
}

void NewGameState::update(float dt)
{
	this->updateInput();
}

void NewGameState::render()
{
	this->graphicsManager->renderShape(&background);
}

void NewGameState::resetState()
{
}
