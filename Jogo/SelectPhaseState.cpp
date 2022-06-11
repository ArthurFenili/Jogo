#include "SelectPhaseState.h"

SelectPhaseState::SelectPhaseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;

	this->initButtons();
}

SelectPhaseState::~SelectPhaseState()
{
	delete this->forestPhaseButton;
	delete this->castlePhaseButton;
	delete this->backButton;
}

void SelectPhaseState::initButtons()
{
	this->forestPhaseButton = new Button(
		1280.f / 2 - 150,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Forest Phase",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(forestPhaseButton);

	this->castlePhaseButton = new Button(
		1280.f / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Castle Phase",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(castlePhaseButton);

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

void SelectPhaseState::updateButtons()
{
	this->forestPhaseButton->update(this->mousePosView);
	this->castlePhaseButton->update(this->mousePosView);
	this->backButton->update(this->mousePosView);
}

void SelectPhaseState::renderButtons()
{
	this->graphicsManager->renderShape(this->forestPhaseButton->getShape());
	this->graphicsManager->renderText(this->forestPhaseButton->getText());

	this->graphicsManager->renderShape(this->castlePhaseButton->getShape());
	this->graphicsManager->renderText(this->castlePhaseButton->getText());

	this->graphicsManager->renderShape(this->backButton->getShape());
	this->graphicsManager->renderText(this->backButton->getText());
}

void SelectPhaseState::updateInput()
{
	if (forestPhaseButton->isPressed()) {
		PlayingState::forestPhase = true;
		State* newGame = new NewGameState(this->graphicsManager, this->states, this->dt);
		this->insertState(newGame, true);
		this->updateStateChange();
	}
	if (castlePhaseButton->isPressed()) {
		PlayingState::forestPhase = false;
		State* newGame = new NewGameState(this->graphicsManager, this->states, this->dt);
		this->insertState(newGame, true);
		this->updateStateChange();
	}
	if (backButton->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
}