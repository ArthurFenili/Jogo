#include "GameOverState.h"
#include "PlayingState.h"

GameOverState::GameOverState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)

{
	this->dt = dt;

	//---------------
	this->initButtons();
}

GameOverState::~GameOverState()
{
	delete this->playAgain;
	delete this->saveGame;
	delete this->mainMenu;
}

void GameOverState::initButtons()
{
	this->playAgain = new Button(
		1280.f / 2 - 150,
		150.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Play Again",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(playAgain);

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

void GameOverState::updateButtons()
{
	this->playAgain->update(this->mousePosView);
	this->saveGame->update(this->mousePosView);
	this->mainMenu->update(this->mousePosView);
}

void GameOverState::renderButtons()
{
	this->graphicsManager->renderShape(this->playAgain->getShape());
	this->graphicsManager->renderText(this->playAgain->getText());

	this->graphicsManager->renderShape(this->saveGame->getShape());
	this->graphicsManager->renderText(this->saveGame->getText());

	this->graphicsManager->renderShape(this->mainMenu->getShape());
	this->graphicsManager->renderText(this->mainMenu->getText());
}

void GameOverState::renderTxt()
{
	sf::Text* txt;
	txt = new sf::Text();
	txt->setString("GAME OVER");
	txt->setFont(this->font);
	txt->setFillColor(sf::Color::White);
	txt->setCharacterSize(64);
	txt->setPosition(sf::Vector2f((this->graphicsManager->getWindow()->getSize().x / 2.f) - 200, (float)20));

	this->graphicsManager->renderText(txt);
}

void GameOverState::updateInput()
{
	if (this->playAgain->isPressed()) {
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}

	if (this->saveGame->isPressed()) {

		name = inputManager.readString(this->graphicsManager);

		this->writeToLeaderboardFile();
	}

	if (this->mainMenu->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
}