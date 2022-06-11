#include "VictoryState.h"
#include "PlayingState.h"

VictoryState::VictoryState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	PlayingState::enteredDoor = false;
	PlayingState::defeatedBoss = false;
	this->dt = dt;
	this->initButtons();
}

VictoryState::~VictoryState()
{
	delete this->saveGame;
	delete this->mainMenu;
}

void VictoryState::initButtons()
{
	this->saveGame = new Button(
		1280.f / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Save Game",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(saveGame);

	this->mainMenu = new Button(
		1280.f / 2 - 150,
		450.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Main Menu",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(mainMenu);
}

void VictoryState::updateButtons()
{
	this->saveGame->update(this->mousePosView);
	this->mainMenu->update(this->mousePosView);
}

void VictoryState::renderButtons()
{
	this->graphicsManager->renderShape(this->saveGame->getShape());
	this->graphicsManager->renderText(this->saveGame->getText());

	this->graphicsManager->renderShape(this->mainMenu->getShape());
	this->graphicsManager->renderText(this->mainMenu->getText());
}

void VictoryState::renderTxt()
{
	sf::Text* txt;
	txt = new sf::Text();
	txt->setString("VICTORY");
	txt->setFont(this->font);
	txt->setFillColor(sf::Color::White);
	txt->setCharacterSize(64);
	txt->setPosition(sf::Vector2f((this->graphicsManager->getWindow()->getSize().x / 2.f) - 140, (float)100));

	this->graphicsManager->renderText(txt);
}

void VictoryState::updateInput()
{
	if (this->saveGame->isPressed()) {

		name = inputManager.readString(this->graphicsManager);

		this->writeToLeaderboardFile();
	}

	if (this->mainMenu->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
}