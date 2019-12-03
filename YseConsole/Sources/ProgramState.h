#pragma once
#include <memory>
#include "MainLoop.h"



/*
 *	IProgramState represents Program's inner state.
 *	use "state pattern".
 *
 *	if class derived from this, add prefix 'P' in front of class.
 */
class IProgramState
{
public:
	/* constructor and destructor */
	IProgramState() = default;
	virtual ~IProgramState() = default;

	/* execute current program's state */
	virtual void Execute() = 0;
};





/*	PMainMenu represents Console's main menu state. */
class PMainMenu : public IProgramState
{
public:
	/* constructor and destructor */
	PMainMenu();
	~PMainMenu() = default;

public:
	/* inherited by IProgramState */
	virtual void Execute() override;

private:
	/* console render pointer */
	class ConsoleRender* pConsoleRender;
};





/*
 *	StateManager manages all of inner states.
 *	Main features of StateManager is to change and
 *	execute each inner state.
 */
class StateManager : public IUpdateEntity
{
public:
	/* constructor and destructor */
	StateManager();
	~StateManager() = default;

	/* translate to next state and update */
	void Translate(IProgramState* NextState);

public:
	/* inherited by IUpdateEntity */
	virtual bool Update(float DeltaTime) override;

private:
	/* program's current inner state */
	IProgramState* CurrentState;

	/* all states */
	std::unique_ptr<PMainMenu> uMainMenu;
};