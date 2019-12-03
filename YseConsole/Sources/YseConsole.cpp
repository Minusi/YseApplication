#include "YseConsole.h"

#include <iostream>
#include <thread>
#include "yse.hpp"

#include <wtypes.h>
#include <Windows.h>
#include <cstdlib>

#include "Configuration.h"
#include "Console.h"
#include "MainLoop.h"
#include "ProgramState.h"

using namespace std;


/**************************************************
 *               global variables                 *
 **************************************************/
YseProgram* gYseProgram = new YseProgram();
/**************************************************
 *               global variables                 *
 **************************************************/





YseProgram* YseProgram::ValidateProgram(YseProgram* InProgram)
{
	/* exit if program is not valid */
	if (InProgram == nullptr)
		exit(EXIT_FAILURE);

	return InProgram;
}

void YseProgram::Start()
{
	/* escape if program is already initialized */
	if (bProgramInit == true)
		return;

	/* set init flag and initialize program */
	bProgramInit = true;
	Init();
}

void YseProgram::Init()
{
	/* Initialize YSE System */
	YSE::System().init();

	{
		/* get window rect for relocation console(in center) */
		RECT RectScreen;
		GetWindowRect(GetDesktopWindow(), &RectScreen);

		/* calculate console position */
		int Left = ((RectScreen.right - RectScreen.left) - APP::DefaultConsoleWidth) / 2;
		int Top = ((RectScreen.bottom - RectScreen.top) - APP::DefaultConsoleHeight) / 2;
		uConsole = unique_ptr<Console>(new Console(Left, Top, APP::DefaultConsoleWidth, APP::DefaultConsoleHeight));
	}

	/* Initialize others */
	{
		uMainLoop = unique_ptr<MainLoop>(new MainLoop());
		uStateManager = unique_ptr<StateManager>(new StateManager());
	}

	/* start loop */
	uMainLoop->Loop();
}

void YseProgram::Close()
{
	/* Close the Yse System */
	YSE::System().close();
}



UpdateDelegate* YseProgram::OnUpdateDelegate() const
{
	/* get Mainloop and check validation */
	MainLoop* Loop = uMainLoop.get();
	if (Loop == nullptr)
		return nullptr;
	
	return Loop->OnUpdateDelegate();
}

ConsoleRender* YseProgram::GetConsoleRender() const
{
	/* return null if console is not valid */
	Console* pConsole = uConsole.get();
	if (pConsole == nullptr)
		return nullptr;

	return pConsole->GetConsoleRender();
}

Console* YseProgram::GetConsole() const
{
	return uConsole.get();
}






/* console application's main entry point */
int main()
{
	//STARTUPINFO StartupInfo = { 0 };
	//PROCESS_INFORMATION ProcessInfo;

	//StartupInfo.cb = sizeof(StartupInfo);

	//if (CreateProcess
	//(
	//	NULL,
	//	APP::DEBUG::Command,
	//	NULL,
	//	NULL,
	//	false,
	//	CREATE_NEW_CONSOLE,
	//	NULL,
	//	NULL,
	//	&StartupInfo,
	//	&ProcessInfo
	//) == false)
	//{
	//	cout << "false\n";
	//}

		
	gYseProgram->Start();
	delete(gYseProgram);
	return 0;
}
