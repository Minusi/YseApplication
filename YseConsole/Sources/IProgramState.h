#pragma once

using namespace std;



/* 
 *	IProgramState represents Program's inner state.
 *	use "state pattern".
 */
class IProgramState
{
public:
	/* execute current program's state */
	virtual void Execute() = 0;
};





/*
 *	StateManager manages all of inner states.
 *	Main features of StateManager is to change and
 *	execute each inner state.
 */
class StateManager
{
public:
	/* default constructor */
	StateManager() = default;

	/* translate to next state and update */
	void Translate(IProgramState* NextState);

private:
	/* program's current inner state */
	IProgramState* CurrentState;
};