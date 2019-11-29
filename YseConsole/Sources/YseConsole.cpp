#include <iostream>
#include <thread>
#include "yse.hpp"
#include <Windows.h>


using namespace std;


/*
 *	YseConsole is represented for Console Application. Main purpose of
 *	class is abstraction about 'console program'.
 */
class YseConsole
{
public:
	/* Default Constructor */
	YseConsole() : bMainLoop(true){ }

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
	/* flag for checking main loop can still loop */
	bool bMainLoop;
} gYseConsole;

void YseConsole::Start()
{
	Init();
	Loop();
}

void YseConsole::Init()
{
	/* Initialize YSE System */
	YSE::System().init();
}

void YseConsole::Close()
{
	/* Close the YSE System */
	YSE::System().close();
}





void YseConsole::Loop()
{
	while (bMainLoop)
	{

	}

	Close();
}

int main()
{
	gYseConsole.Start();
	return 0;
}
