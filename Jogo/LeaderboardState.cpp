#include "LeaderboardState.h"

LeaderboardState::LeaderboardState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt) :
	State(graphicsManager, states, dt)

{
	this->dt = dt;

	//---------------
	this->initButtons();

	this->buildLeaderboard();
}

LeaderboardState::~LeaderboardState()
{
	delete this->backButton;
}

void LeaderboardState::initButtons()
{
	this->backButton = new Button(
		1280.f / 2 - BUTTON_WIDTH / 2,
		500.f,
		BUTTON_WIDTH, BUTTON_HEIGHT,
		&this->font, "Back",
		sf::Color(0, 0, 0, 255),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200)
	);
	this->buttonList.addButton(backButton);
}

void LeaderboardState::buildLeaderboard()
{
	std::ifstream file;

	file.open("saves/leaderboard.txt", std::ios::binary | std::ios::in);

	std::string name;
	std::string textString = "";
	std::string pointsString;

	sf::Text* txt;

	int i = 1;
	while (file >> pointsString >> name) {
		textString = "0" + std::to_string(i) + " - " + name + "........" + pointsString;
		i++;

		txt = new sf::Text();
		txt->setString(textString);
		txt->setFont(this->font);
		txt->setFillColor(sf::Color::White);
		txt->setCharacterSize(56);
		txt->setPosition(sf::Vector2f((this->graphicsManager->getWindow()->getSize().x / 2.f) - 270, (float)50 * i));

		vectorString.push_back(txt);
	}

	file.close();
}

void LeaderboardState::renderTxt()
{
	for (iterator = vectorString.begin(); iterator != vectorString.end(); iterator++) {
		this->graphicsManager->renderText(*iterator);
	}
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