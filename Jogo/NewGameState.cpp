#include "NewGameState.h"

NewGameState::NewGameState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;

	this->initBackground();
	this->initFonts();
	this->initButtons();
}

NewGameState::~NewGameState()
{
	delete this->onePlayerButton;
	delete this->twoPlayersButton;
	delete this->backButton;
}

void NewGameState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void NewGameState::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void NewGameState::initButtons()
{
	this->onePlayerButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "One Player",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->twoPlayersButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Two Players",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->backButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Back",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
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
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt, false), true);
		this->updateStateChange();
	}

	if (twoPlayersButton->isPressed()) {
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt, true), true);
		this->updateStateChange();
	}
}

void NewGameState::update(float dt)
{
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void NewGameState::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}

void NewGameState::resetState()
{
}
