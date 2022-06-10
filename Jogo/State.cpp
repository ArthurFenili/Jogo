#include "State.h"

State::State(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt)
{
	this->dt = dt;
	this->id = STATE;

	this->states = states;
	this->graphicsManager = graphicsManager;

	this->initBackground();
	this->initFonts();
}

State::~State()
{
	this->buttonList.clearList();
}

void State::initBackground()
{
	this->background.setSize(sf::Vector2f(1280.f, 720.f));

	if (!this->backgroundTexture.loadFromFile("images/background.jpg"))
		throw "ERROR::BACKGROUND_TEXTURE::COULD_NOT_LOAD_FROM_FILE";

	this->background.setTexture(&this->backgroundTexture);
}

void State::initFonts()
{
	if (!this->font.loadFromFile("fonts/georgia.ttf"))
		throw "ERROR::FONT::COULD_NOT_LOAD_FROM_FILE";
}

void State::insertState(State* pState, bool replace)
{
	this->insert = true;
	this->newState = pState;

	this->replace = replace;
}

void State::removeCurrentState()
{
	this->remove = true;
}

void State::updateStateChange()
{
	if (this->remove && (!this->states->empty())) {
		this->states->pop();

		if (!this->states->empty()) {
			this->states->top()->start();
		}
		this->remove = false;
	}

	if (this->insert) {
		if (this->replace && (!this->states->empty())) {
			this->states->pop();
			this->replace = false;
		}

		if ((!this->states->empty())) {
			this->states->top()->pause();
		}
		this->states->push(this->newState);
		this->insert = false;
	}
}

State& State::getCurrentState()
{
	return (*states->top());
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->graphicsManager->getWindow());
	this->mousePosView = this->graphicsManager->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->graphicsManager->getWindow()));

}

void State::update(float dt)
{
	float aspectRatio = (float)this->graphicsManager->getWindow()->getSize().x / (float)this->graphicsManager->getWindow()->getSize().y;
	this->graphicsManager->setViewSize(sf::Vector2f(1280.f * aspectRatio, 720.f));
	this->updateInput();
	this->updateMousePositions();
	this->updateButtons();
}

void State::render()
{
	this->graphicsManager->clearWindow(-1);

	this->graphicsManager->renderShape(&background);
	this->renderButtons();
}
