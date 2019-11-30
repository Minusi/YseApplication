#include <iostream>
#include <thread>
#include <memory>
#include "yse.hpp"

#include <Windows.h>
#include <wtypes.h>

#include "Console.h"
#include "Configuration.h"
#include "MainLoop.h"


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
	YseConsole() = default;

	YseConsole(const YseConsole& other) = delete;
	YseConsole(const YseConsole&& other) = delete;
	const YseConsole& operator=(const YseConsole& other) = delete;

	/* Start Yse console application. Used for Application Main Entry. */
	void Start();

private:
	/* Initialize console application */
	void Init();

	/* Clean up consle application and exit. */
	void Close();



private:
	/* Console Object */
	unique_ptr<Console> pConsole;

	/* supports Loop */
	unique_ptr<MainLoop> pMainLoop;
};



void YseConsole::Start()
{
	Init();
}

void YseConsole::Init()
{
	/* Initialize YSE System */
	YSE::System().init();

	/* get window rect for relocation console(in center) */
	RECT RectScreen;
	GetWindowRect(GetDesktopWindow(), &RectScreen);

	/* calculate console position */
	int Left = ((RectScreen.right - RectScreen.left) - APP::DefaultConsoleWidth) / 2;
	int Top = ((RectScreen.bottom - RectScreen.top) - APP::DefaultConsoleHeight) / 2;

	/* initialize member variables */
	pConsole = unique_ptr<Console>(new Console(Left, Top, APP::DefaultConsoleWidth, APP::DefaultConsoleHeight));
	pMainLoop = unique_ptr<MainLoop>(new MainLoop());



	/* start loop */
	pMainLoop->Loop();
}

void YseConsole::Close()
{
	/* Close the Yse System */
	YSE::System().close();
}






/* console application's main entry point */
int main()
{
	YseConsole sYseConsole;
	sYseConsole.Start();

	return 0;
}
