#pragma once
#include <Windows.h>
#include <utility>
#include <memory>
#include <string>

#include "Configuration.h"
#include "MainLoop.h"



/*
 *	ConsoleRender has a responsibility for 
 *	console rendering. all renderable(i.e. string)
 *	must be rendered through this class.
 */
class ConsoleRender : public IUpdateEntity 
{
public:
	/* constructor and destructor */
	ConsoleRender() = delete;
	~ConsoleRender(); 
	ConsoleRender(SHORT InCols, SHORT InLines, char InDecoration = APP::DefaultDecoration);

	/* fills line with specified Character */
	void FillCharacter(char Character = ' ');

	/* fills line with specified Decoration */
	void FillDecoration(char Decoration = APP::DefaultDecoration);

	/* fill remainder of console blank lines 
	 * - Decoration : if -1, does not decorate 
	 * - bIncludeBottom : if true, the bottommost will be also filled */
	void FillBlankLines(char Decoration = APP::DefaultDecoration, unsigned int NumDeco = 1, bool bIncludeBottom = false);
private:
	/* internal function for fill one line */
	void FillLine(char Target);

public:
	/* align text to left alignment 
	 * - Text : text to output console 
	 * - Decoration : decoration character. if -1 and NumDeco is 0, doesn't decorate
	 * - NumDeco : number of decoration character. if 0, doesn't decorate */
	void LeftAlignment(std::string Text, char Decoration = -1, unsigned int NumDeco = 1);

	/* align text to center alignment */
	void CenterAlignment(std::string Text, char Decoration = -1, unsigned int NumDeco = 1);

	/* align text to right alignment */
	void RightAlignment(std::string Text, char Decoration = -1, unsigned int NumDeco = 1);

private:
	enum class ETextAlignment
	{
		ALIGN_Left, ALIGN_Center, ALIGN_Right
	};
	/* internal function for calculate text alignment */
	void CalculateAlignment(std::string Text, char Decoration, unsigned int NumDeco, ETextAlignment Alignment);

public:
	/* setter function */
	void SetDefaultDecoration(char InChanged);
	void UpdateConsoleSize(SHORT InCols, SHORT InLines);

	/* overrides from IUpdateEntity */
	virtual bool Update(float DeltaTime) override;

	


private:
	/* cached variable of console cols */
	SHORT ConsoleCols;

	/* cached variable of console lines */
	SHORT ConsoleLines;

	/* current lines, should be less than ConsoleLines */
	SHORT CurrentLines;

	/* character for decorating console */
	char DefaultDecoration;
};





/*	Console class is represented for Windows console.
 *	internally, it is mostly implemented by wrapper function.
 */
class Console
{
public:
	/* constructor and destructor */
	Console(int Left, int Top, int Width, int Height);
	~Console() = default;

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
		return uConsoleRender.get();
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

	/* console render obejct based on text interface */
	std::unique_ptr<ConsoleRender> uConsoleRender;
};



