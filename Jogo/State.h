/*#pragma once

class StateMachine;

enum stateID {
	unknown = -1,
	mainMenu = 0,
	newGame,
	playing,
	pauseMenu,
	leaderboard
};

class State
{
protected:
	StateMachine* pSM;
	stateID id;

public:
	State(StateMachine* pSM = nullptr, stateID id = unknown);
	~State();

	void setStateMachine(StateMachine* pSM);
	void changeState(stateID id);
	stateID getID();

	virtual void update(const float dt) = 0;
	virtual void render() = 0;
	virtual void resetState() = 0;
};

*/