#include "MainMenuState.h"

MainMenuState::MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	std::cout << "MainMenuState" << std::endl;

	this->dt = dt;

	//---------------
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	delete this->newGameButton;
	delete this->exitButton;
	delete this->continueButton;
	delete this->leaderboardButton;
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void MainMenuState::initButtons()
{
	this->newGameButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - BUTTON_WIDTH / 2,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "New Game",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->continueButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - BUTTON_WIDTH / 2,
		250.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Continue",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->leaderboardButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - BUTTON_WIDTH / 2,
		400.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Leaderboard",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);

	this->exitButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - BUTTON_WIDTH / 2,
		550.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Exit",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
}

void MainMenuState::updateButtons()
{
	this->newGameButton->update(this->mousePosView);
	this->continueButton->update(this->mousePosView);
	this->leaderboardButton->update(this->mousePosView);
	this->exitButton->update(this->mousePosView);
}

void MainMenuState::renderButtons()
{
	this->graphicsManager->renderShape(this->newGameButton->getShape());
	this->graphicsManager->renderText(this->newGameButton->getText());

	this->graphicsManager->renderShape(this->continueButton->getShape());
	this->graphicsManager->renderText(this->continueButton->getText());

	this->graphicsManager->renderShape(this->leaderboardButton->getShape());
	this->graphicsManager->renderText(this->leaderboardButton->getText());

	this->graphicsManager->renderShape(this->exitButton->getShape());
	this->graphicsManager->renderText(this->exitButton->getText());
}

void MainMenuState::updateInput()
{
	if (newGameButton->isPressed()) {
		State* newGame = new NewGameState(this->graphicsManager, this->states, this->dt);
		this->insertState(newGame);
		this->updateStateChange();
	}
	if (exitButton->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
		this->graphicsManager->closeWindow();
	}
}

void MainMenuState::update(float dt)
{
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void MainMenuState::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}

void MainMenuState::resetState()
{
}
