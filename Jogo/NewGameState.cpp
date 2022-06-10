#include "NewGameState.h"

NewGameState::NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;

	this->initButtons();
}

NewGameState::~NewGameState()
{
	delete this->onePlayerButton;
	delete this->twoPlayersButton;
	delete this->backButton;
}

void NewGameState::initButtons()
{
	this->onePlayerButton = new Button(
		1280.f / 2 - 150,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "One Player",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(onePlayerButton);

	this->twoPlayersButton = new Button(
		1280.f / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Two Players",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(twoPlayersButton);

	this->backButton = new Button(
		1280.f / 2 - 150,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Back",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(backButton);
}

void NewGameState::updateButtons()
{
	this->onePlayerButton->update(this->mousePosView);
	this->twoPlayersButton->update(this->mousePosView);
	this->backButton->update(this->mousePosView);
}

void NewGameState::renderButtons()
{
	this->graphicsManager->renderShape(this->onePlayerButton->getShape());
	this->graphicsManager->renderText(this->onePlayerButton->getText());

	this->graphicsManager->renderShape(this->twoPlayersButton->getShape());
	this->graphicsManager->renderText(this->twoPlayersButton->getText());

	this->graphicsManager->renderShape(this->backButton->getShape());
	this->graphicsManager->renderText(this->backButton->getText());
}

void NewGameState::updateInput()
{
	if (backButton->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
	if (onePlayerButton->isPressed()) {
		PlayingState::twoPlayers = false;
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}

	if (twoPlayersButton->isPressed()) {
		PlayingState::twoPlayers = true;
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}
}
