#include "PauseState.h"
#include "PlayingState.h"

PauseState::PauseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt, bool* exit, Phase* currentPhase) :
	State(graphicsManager, states, dt)
{
	this->dt = dt;
	this->exitGame = exit;
	this->currentPhase = currentPhase;

	this->initButtons();
}

PauseState::~PauseState()
{
	delete this->continueButton;
	delete this->saveButton;
	delete this->exitButton;
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
	this->buttonList.addButton(continueButton);

	this->saveButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		300.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Save",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(saveButton);

	this->exitButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - 150,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Exit",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(exitButton);
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

	if (saveButton->isPressed())
	{
		this->entityList = this->currentPhase->getEntityList();

		this->writeToSavedGameFile();
	}
	if (exitButton->isPressed()) {
		*exitGame = true;
		this->removeCurrentState();
		this->updateStateChange();
	}
}

void PauseState::writeToSavedGameFile()
{
	// ----------------------- write
	std::ofstream writeFile;

	writeFile.open("saves/savedGame.txt", std::ios::out | std::ios::trunc);

	int numPlayers = PlayingState::twoPlayers ? 2 : 1;

	if (numPlayers > 1) {
		writeFile << entityList->operator[](entityList->getSize() - 2)->getPosition().x << std::endl;
		writeFile << entityList->operator[](entityList->getSize() - 2)->getPosition().y << std::endl;
		writeFile << entityList->operator[](entityList->getSize() - 2)->getId() << std::endl;
	}
	if (numPlayers >= 1) {
		writeFile << entityList->operator[](entityList->getSize() - 1)->getPosition().x << std::endl;
		writeFile << entityList->operator[](entityList->getSize() - 1)->getPosition().y << std::endl;
		writeFile << entityList->operator[](entityList->getSize() - 1)->getId() << std::endl;
	}

	for (int i = 0; i < entityList->getSize() - numPlayers; i++) {
		writeFile << entityList->operator[](i)->getPosition().x << std::endl;
		writeFile << entityList->operator[](i)->getPosition().y << std::endl;
		writeFile << entityList->operator[](i)->getId() << std::endl;
	}

	writeFile.close();

	writeFile.open("saves/savedPhase.txt", std::ios::out | std::ios::trunc);

	writeFile << PlayingState::forestPhase << std::endl;
	writeFile << PlayingState::twoPlayers << std::endl;

	writeFile.close();
}
