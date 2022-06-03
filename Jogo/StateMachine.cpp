/*#include "StateMachine.h"

StateMachine::StateMachine()
{
	lastStateID = unknown;
	currentStateID = unknown;
}

StateMachine::~StateMachine()
{
	while (stackOfStates.size() > 0) {
		delete stackOfStates.top();
		stackOfStates.pop();
	}
}

//void StateMachine::changeCurrentState(stateID id)
//{
//}

void StateMachine::updateCurrentState(const float dt)
{
	stackOfStates.top()->update(dt);
}

void StateMachine::renderCurrentState()
{
	stackOfStates.top()->render();
}

stateID StateMachine::getCurrentStateID()
{
	return stateID();
}

void StateMachine::insertState(State* pState)
{
	if (pState == nullptr) {
		std::cout << "ERROR: pointer to state is nullptr on StateMachine::insertState()" << std::endl;
	}
	stackOfStates.push(pState);
}

stateID StateMachine::getLastStateID()
{
	return lastStateID;
}
*/