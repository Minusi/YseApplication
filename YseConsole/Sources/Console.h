#pragma once
#include <Windows.h>
#include <utility>
#include <memory>
#include <string>
#include "Configuration.h"
#include "MainLoop.h"

using namespace std;



class ConsoleRender : public IUpdateEntity 
{
public:
	ConsoleRender() = delete;
	ConsoleRender(SHORT InCols, SHORT InLines, char InDecoration = APP::DefaultDecoration)
		: ConsoleCols(InCols)
		, ConsoleLines(InLines)
		, DefaultDecoration(InDecoration)
	{ }

	/* fill line with specified Character */
	void FillLine(char Character);

	/* align text to left alignment 
	 * - Text : text to output console 
	 * - Decoration : decoration character. if -1, doesn't decorate
	 * - NumDeco : number of decoration character. if 0, doesn't decorate */
	void LeftAlignment(string Text, char Decoration = -1, unsigned int NumDeco = 1);

	/* align text to center alignment */
	void CenterAlignment(string Text, char Decoration = -1, unsigned int NumDeco = 1);

	/* align text to right alignment */
	void RightAlignment(string Text, char Decoration = -1, unsigned int NumDeco = 1);

private:
	enum class ETextAlignment
	{
		ALIGN_Left, ALIGN_Center, ALIGN_Right
	};
	/* internal function for calculate text alignment */
	void CalculateAlignment(string Text, char Decoration, unsigned int NumDeco, ETextAlignment Alignment);
public:
	/* overrides from IUpdateEntity */
	virtual bool Update() override;

	


private:
	/* cached variable of console cols */
	SHORT ConsoleCols;

	/* cached variable of console lines */
	SHORT ConsoleLines;

	/* character for decorating console */
	char DefaultDecoration;
};





/*	Console class is represented for Windows console.
 *	internally, it is mostly implemented by wrapper function.
 */
class Console
{
public:
	/* default constructor */
	Console(int Left, int Top, int Width, int Height);

	Console() = delete;
	Console(const Console& Other) = delete;
	Console(const Console&& Other) = delete;
	const Console& operator=(const Console& Other) = delete;

public:
	/* wrapper function for 'MoveWindow' */
	void SetWindowSize(int Left, int Top, int Width, int Height);

	/* getter functions */
	inline SHORT GetConsoleCols() const
	{
		return Cols;
	}
	inline SHORT GetConsoleLines() const
	{
		return Lines;
	}
	inline std::pair<SHORT, SHORT> GetConsoleColsAndLines() const
	{
		return { Cols, Lines };
	}
	inline ConsoleRender* GetConsoleRender() const
	{
		return pConsoleRender.get();
	}
	


private:
	/* handle to console */
	HANDLE ConsoleHandle;

	/* window handle to console */
	HWND ConsoleWHandle;
	
	/* console cols( number of character in one lines ) */
	SHORT Cols;

	/* console lines */
	SHORT Lines;

public:
	std::unique_ptr<ConsoleRender> pConsoleRender;
};