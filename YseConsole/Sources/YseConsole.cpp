#include <iostream>
#include <thread>
#include "yse.hpp"

#include <Windows.h>
#include <wtypes.h>

#include "Console.h"
#include "Configuration.h"


using namespace std;
class Console;

/*
 *	YseConsole is represented for Console Application. Main purpose of
 *	class is abstraction about 'console program'.
 */
class YseConsole
{
public:
	/* Default Constructor */
	YseConsole() : bMainLoop(true), mConsole(nullptr)
	{
	}

	YseConsole(const YseConsole& other) = delete;
	YseConsole(const YseConsole&& other) = delete;
	const YseConsole& operator=(const YseConsole& other) = delete;

	/* Start Yse console application. Used for Application Main Entry. */
	void Start();

private:
	/* Initialize console application */
	void Init();

	/* Main loop */
	void Loop();

	/* Clean up consle application and exit. */
	void Close();



private:
	Console* mConsole;

	/* flag for checking main loop can still loop */
	bool bMainLoop;

};

void YseConsole::Start()
{
	Init();
	Loop();
}

void YseConsole::Init()
{
	/* Initialize YSE System */
	YSE::System().init();

	if (mConsole != nullptr)
		return;


	/* get window rect for relocation console(in center) */
	RECT RectScreen;
	GetWindowRect(GetDesktopWindow(), &RectScreen);

	/* calculate console position */
	int Left = ((RectScreen.right - RectScreen.left) - APP::ConsoleDefaultWidth) / 2;
	int Top = ((RectScreen.bottom - RectScreen.top) - APP::ConsoleDefaultHeight) / 2;

	/* initialize console */
	mConsole = new Console(Left, Top, APP::ConsoleDefaultWidth, APP::ConsoleDefaultHeight);
}

void YseConsole::Close()
{
	/* Close the Yse System */
	YSE::System().close();
}





void YseConsole::Loop()
{
	while (bMainLoop)
	{
	}

	Close();
}

/* console application's main entry point */
int main()
{
	YseConsole sYseConsole;
	sYseConsole.Start();
	return 0;
}
