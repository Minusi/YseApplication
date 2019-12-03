#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


#include "ProgramState.h"
#include <string>
#include <array>

#include "YseConsole.h"
#include "Console.h"

using namespace std;



StateManager::StateManager()
	:uMainMenu(unique_ptr<PMainMenu>(new PMainMenu()))
{
	CurrentState = uMainMenu.get();

	/* get UpdateDelegate and register this to update every frame */
	auto Publisher = YseProgram::ValidateProgram(gYseProgram)->OnUpdateDelegate();
	Publisher->Register(this);
}

void StateManager::Translate(IProgramState* NextState)
{
	CurrentState = NextState;

	if (CurrentState != nullptr)
		CurrentState->Execute();
}

bool StateManager::Update(float DeltaTime)
{
	if (CurrentState == nullptr)
		return false;

	CurrentState->Execute();
	return true;
}


PMainMenu::PMainMenu()
	: pConsoleRender(nullptr)
{
	/* escape if is nullptr */
	if (gYseProgram == nullptr)
		return;

	pConsoleRender = gYseProgram->GetConsoleRender();
}

void PMainMenu::Execute()
{
	if (pConsoleRender == nullptr)
		return;
	//system("cls");

	array<string, 5> MenuList;
	MenuList[0] = "1. Play";
	MenuList[1] = "2. Edit";
	MenuList[2] = "3. None";
	MenuList[3] = "4. Info";
	MenuList[4] = "5. Exit";

	pConsoleRender->FillDecoration();
	//for (const auto& it : MenuList)
	//	pConsoleRender->LeftAlignment(it);
	pConsoleRender->FillBlankLines();
	pConsoleRender->FillDecoration();

}
