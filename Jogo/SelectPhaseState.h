#pragma once
#include "State.h"
#include "NewGameState.h"
#include "PlayingState.h"

class SelectPhaseState :
    public State
{
private:
    Button* forestPhaseButton;
    Button* castlePhaseButton;
    Button* backButton;
public:
    SelectPhaseState(GraphicsManager* graphicsManager, std::stack<State*>* states, float* dt);
    ~SelectPhaseState();

    void initButtons();

    void updateButtons();
    void renderButtons();

    void updateInput();
};
