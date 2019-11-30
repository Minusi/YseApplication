#include "IProgramState.h"



void StateManager::Translate(IProgramState* NextState)
{
	CurrentState = NextState;

	if (CurrentState != nullptr)
		CurrentState->Execute();
}
