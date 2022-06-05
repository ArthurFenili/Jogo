#pragma once

#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"

class State
{
protected:
	State* newState;
	std::stack<State*>* states;
	GraphicsManager* graphicsManager;
	float* dt;

	bool insert;
	bool replace;
	bool remove;
public:
	State(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	virtual ~State();

	void insertState(State* pState, bool replace = false);
	void removeCurrentState();
	void updateStateChange();
	State& getCurrentState();

	virtual void updateInput() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void resetState() = 0;

	virtual void pause() {};
	virtual void start() {};
};
