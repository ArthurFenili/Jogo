#include "PauseState.h"

PauseState::PauseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool* exit) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;
	this->exitGame = exit;

	this->initBackground();
	this->initFonts();
	this->initButtons();
}

PauseState::~PauseState()
{
	delete this->continueButton;
	delete this->saveButton;
	delete this->exitButton;
}

void PauseState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void PauseState::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void PauseState::initButtons()
{
	this->continueButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Continue",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->saveButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Save",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->exitButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Exit",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
}

void PauseState::updateButtons()
{
	this->continueButton->update(this->mousePosView);
	this->saveButton->update(this->mousePosView);
	this->exitButton->update(this->mousePosView);
}

void PauseState::renderButtons()
{
	this->graphicsManager->renderShape(this->continueButton->getShape());
	this->graphicsManager->renderText(this->continueButton->getText());

	this->graphicsManager->renderShape(this->saveButton->getShape());
	this->graphicsManager->renderText(this->saveButton->getText());

	this->graphicsManager->renderShape(this->exitButton->getShape());
	this->graphicsManager->renderText(this->exitButton->getText());
}

void PauseState::updateInput()
{
	if (continueButton->isPressed()) {

		this->removeCurrentState();
		this->updateStateChange();
	}
	if (exitButton->isPressed()) {
		*exitGame = true;
		this->removeCurrentState();
		this->updateStateChange();
	}
}

void PauseState::update(float dt)
{
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void PauseState::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}

void PauseState::resetState()
{
}