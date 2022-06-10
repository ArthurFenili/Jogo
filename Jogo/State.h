#pragma once

#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Ent.h"
#include "Button.h"
#include "ButtonList.h"

const float BUTTON_WIDTH = 300;
const float BUTTON_HEIGHT = 100;

class State :
	public Ent
{
protected:
	State* newState;
	std::stack<State*>* states;

	ButtonList buttonList;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	bool insert;
	bool replace;
	bool remove;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	State(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
	State() {}
	virtual ~State();

	void initBackground();
	void initFonts();
	void initButtons() {}

	void insertState(State* pState, bool replace = false);
	void removeCurrentState();
	void updateStateChange();
	State& getCurrentState();

	virtual void updateMousePositions();
	virtual void updateInput() = 0;
	virtual void updateButtons() {}
	virtual void update(float dt);

	virtual void render();
	virtual void renderButtons() {}

	virtual void pause() {};
	virtual void start() {};
};
