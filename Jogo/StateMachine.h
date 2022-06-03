/*#pragma once
#include "State.h"
#include<stack>
#include<iostream>

class StateMachine
{
protected:
	stateID currentStateID;
	stateID lastStateID;

	std::stack<State*> stackOfStates;

public:
	StateMachine();
	~StateMachine();

	//void changeCurrentState(stateID id);
	void updateCurrentState(const float dt);
	void renderCurrentState();
	stateID getCurrentStateID();
	void insertState(State* pState);
	stateID getLastStateID();

};

*/