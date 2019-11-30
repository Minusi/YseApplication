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
 *	YseProgram is represented for Console Application. Main purpose of
 *	class is abstraction about 'console program'.
 */
class YseProgram
{
public:
	/* Default Constructor */
	YseProgram() = default;

	YseProgram(const YseProgram& other) = delete;
	YseProgram(const YseProgram&& other) = delete;
	const YseProgram& operator=(const YseProgram& other) = delete;

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



void YseProgram::Start()
{
	Init();
}

void YseProgram::Init()
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

void YseProgram::Close()
{
	/* Close the Yse System */
	YSE::System().close();
}






/* console application's main entry point */
int main()
{
	unique_ptr<YseProgram> pYseConsole(new YseProgram());
	pYseConsole->Start();

	return 0;
}
