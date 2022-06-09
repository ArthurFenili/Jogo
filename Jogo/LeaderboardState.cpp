#include "LeaderboardState.h"

LeaderboardState::LeaderboardState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt):
	State(graphicsManager, states, dt)

{
	std::cout << "LeaderboardState" << std::endl;

	this->dt = dt;

	//---------------
	this->initBackground();
	this->initFonts();
	this->initButtons();

}

LeaderboardState::~LeaderboardState()
{
	delete this->backButton;
}

void LeaderboardState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->graphicsManager->getWindow()->getSize()));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void LeaderboardState::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void LeaderboardState::initButtons()
{
	this->backButton = new Button(
		(float)this->graphicsManager->getWindow()->getSize().x / 2 - BUTTON_WIDTH / 2,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Back",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
}

void LeaderboardState::updateButtons()
{
	this->backButton->update(this->mousePosView);
}

void LeaderboardState::renderButtons()
{
	this->graphicsManager->renderShape(this->backButton->getShape());
	this->graphicsManager->renderText(this->backButton->getText());
}

void LeaderboardState::updateInput()
{
	if (backButton->isPressed()) {
		this->removeCurrentState();
		this->updateStateChange();
	}
}

void LeaderboardState::update(float dt)
{
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void LeaderboardState::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}

void LeaderboardState::resetState()
{
}
