#include "MainMenuState.h"

MainMenuState::MainMenuState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;

	//---------------
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	delete this->newGameButton;
	delete this->exitButton;
	delete this->continueButton;
	delete this->leaderboardButton;
}

void MainMenuState::initButtons()
{
	this->newGameButton = new Button(
		1280.f / 2 - BUTTON_WIDTH / 2,
		100.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "New Game",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(newGameButton);

	this->continueButton = new Button(
		1280.f / 2 - BUTTON_WIDTH / 2,
		250.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Continue",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(continueButton);

	this->leaderboardButton = new Button(
		1280.f / 2 - BUTTON_WIDTH / 2,
		400.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Leaderboard",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(leaderboardButton);

	this->exitButton = new Button(
		1280.f / 2 - BUTTON_WIDTH / 2,
		550.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Exit",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(exitButton);
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
		PlayingState::loadGame = false;
		State* selectPhase = new SelectPhaseState(this->graphicsManager, this->states, this->dt);
		this->insertState(selectPhase);
		this->updateStateChange();
	}

	if (continueButton->isPressed()) {
		PlayingState::loadGame = true;
		this->loadPhase();
		this->insertState(new PlayingState(this->graphicsManager, this->states, this->dt));
		this->updateStateChange();
	}

	if (leaderboardButton->isPressed()) {
		State* leaderboard = new LeaderboardState(this->graphicsManager, this->states, this->dt);
		this->insertState(leaderboard);
		this->updateStateChange();
	}

	if (exitButton->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
		this->graphicsManager->closeWindow();
	}
}

void MainMenuState::loadPhase()
{
	// ----------------------- read
	std::ifstream readFile;

	readFile.open("saves/savedPhase.txt", std::ios::in);

	if (readFile) {
		std::string forest;
		std::string twoP;

		std::getline(readFile, forest);
		std::getline(readFile, twoP);

		if (forest == "1")
			PlayingState::forestPhase = true;
		else 
			PlayingState::forestPhase = false;
		if (twoP == "1")
			PlayingState::twoPlayers = true;
		else 
			PlayingState::twoPlayers = false;


		readFile.close();
	}

}
