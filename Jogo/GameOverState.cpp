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

/* INSPIRADO NO TUTORIAL DO MONITOR MATHEUS BURDA */
void GameOverState::writeToLeaderboardFile()
{
	// ----------------------- read
	std::ifstream readFile;

	readFile.open("saves/leaderboard.txt", std::ios::in);
	
	std::multimap<int, std::string> nameAndScoreMap;

	if (readFile) {
		std::string name;
		std::string pointsString;

		for (int i = 0; i < 6; i++) {
			std::getline(readFile, pointsString);
			std::getline(readFile, name);

			if (pointsString.length() > 0)
				nameAndScoreMap.insert(std::pair<int, std::string>(std::stoi(pointsString), name));
		}
		readFile.close();
	}

	// ----------------------- write
	if (PlayingState::score != 0 && name.length() > 1)
		nameAndScoreMap.insert(std::pair<int, std::string>(PlayingState::score, name));

	std::ofstream writeFile;

	writeFile.open("saves/leaderboard.txt", std::ios::out | std::ios::trunc);

	while (nameAndScoreMap.size() > 10)
		nameAndScoreMap.erase(nameAndScoreMap.begin());

	for (auto itr = nameAndScoreMap.rbegin(); itr != nameAndScoreMap.rend(); ++itr) {
		writeFile << (*itr).first << std::endl;
		writeFile << (*itr).second << std::endl;
	}

	writeFile.close();

}
