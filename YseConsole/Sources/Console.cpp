#include "Console.h"
using namespace std;

#include <iostream>
Console::Console(int Left, int Top, int Width, int Height) : HandleConsole(GetConsoleWindow())
{

	SetWindowSize(Left, Top, Width, Height);

	
	/* remove console scroll bar */
	ShowScrollBar(HandleConsole, SB_BOTH, FALSE);
}

void Console::SetWindowSize(int Left, int Top, int Width, int Height)
{
	if (HandleConsole == nullptr)
		return;

	/* update window rect */
	MoveWindow(HandleConsole, Left, Top, Width, Height, true);

	/* if remove this code, ShowScrollBar does not work sometimes.
	 * why this situation is occured? i dont know, but i know that
	 * it needs a little time interval between MoveWindow and Show
	 * ScrollBar functions. 
	 *
	 * in other words, it can be replaced by using 
	 * this_thread::sleep_for(chrono::miliseconds(10)), and so on. */
	UpdateWindow(HandleConsole);
}
