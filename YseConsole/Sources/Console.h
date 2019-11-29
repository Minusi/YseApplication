#pragma once
#include <Windows.h>

/*	Console class is represented for Windows console.
 *	internally, it is mostly implemented by wrapper function.
 */
class Console
{
public:
	/* constructor */
	explicit Console(int Left, int Top, int Width, int Height);

	Console() = delete;
	Console(const Console& Other) = delete;
	Console(const Console&& Other) = delete;
	const Console& operator=(const Console& Other) = delete;

public:
	/* move console window. wrapper function for 'MoveWindow' */
	void SetWindowSize(int Left, int Top, int Width, int Height);

private:
	HWND HandleConsole;
	
};

