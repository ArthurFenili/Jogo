#include "State.h"

State::State(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt)
{
	this->dt = dt;

	this->states = states;
	this->graphicsManager = graphicsManager;
}

State::~State()
{
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
