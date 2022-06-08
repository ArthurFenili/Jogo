#include "GameOverState.h"
#include "PlayingState.h"

GameOverState::GameOverState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)

{
	std::cout << "GameOverState" << std::endl;

	this->dt = dt;

	//---------------
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

GameOverState::~GameOverState()
{
	delete this->playAgain;
	delete this->saveGame;
	delete this->mainMenu;
}

void GameOverState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void GameOverState::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void GameOverState::initButtons()
{
	this->playAgain = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		150.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Play Again",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->saveGame = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Save Game",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->mainMenu = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		450.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Main Menu",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

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

void GameOverState::updateInput()
{
	if (this->playAgain->isPressed()) {
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt), true);
		this->updateStateChange();
	}

	if (this->mainMenu->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
}

void GameOverState::update(float dt)
{
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void GameOverState::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}

void GameOverState::resetState()
{
}
