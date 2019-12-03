#include "Console.h"
#include <iostream>

using namespace std;



ConsoleRender::~ConsoleRender() = default;
/* initializes Line to "Lines - 1" because i want to last line make empty */
ConsoleRender::ConsoleRender(SHORT InCols, SHORT InLines, char InDecoration)
	: ConsoleCols(InCols)
	, ConsoleLines(InLines - 1)
	, CurrentLines(0)
	, DefaultDecoration(InDecoration)
{
}

void ConsoleRender::FillCharacter(char Character)
{
	FillLine(Character);
}

void ConsoleRender::FillDecoration(char Decoration)
{
	FillLine(Decoration);
}

void ConsoleRender::FillBlankLines(char Decoration, unsigned int NumDeco, bool bIncludeBottom)
{
	/* escape if ConsoleLines is not valid */
	if (ConsoleLines <= 0)
		return;

	if (CurrentLines >= ConsoleLines)
		return;

	int TotalFillLines = ConsoleLines - CurrentLines - 1;
	TotalFillLines += bIncludeBottom ? 1 : 0;

	string LineContent;
	if (Decoration < 0 || NumDeco == 0)
	{
		for (int i = 0; i < TotalFillLines; ++i)
			LineContent += '\n';

		cout << LineContent << "\n";
	}
	else
	{
		int NumTextPerLine = ConsoleCols - (NumDeco * 2);

		for (unsigned int i = 0; i < NumDeco; ++i)
			LineContent += Decoration;
		for (unsigned int i = 0; i < NumTextPerLine; ++i)
			LineContent += ' ';
		for (unsigned int i = 0; i < NumDeco; ++i)
			LineContent += Decoration;

		for (int i = 0; i < TotalFillLines; ++i)
			cout << LineContent << "\n";
	}

	CurrentLines += TotalFillLines;
}

void ConsoleRender::FillLine(char Target)
{
	/* return if ConsoleCols is not valid */
	if (ConsoleCols <= 0)
		return;

	if (CurrentLines >= ConsoleLines)
		return;

	/* fill string and print to console output */
	string Content;
	for (int i = 0; i < ConsoleCols; ++i)
		Content += Target;
	cout << Content << "\n";

	CurrentLines++;
}



void ConsoleRender::LeftAlignment(string Text, char Decoration, unsigned int NumDeco)
{
	CalculateAlignment(Text, Decoration, NumDeco, ETextAlignment::ALIGN_Left);
}

void ConsoleRender::CenterAlignment(string Text, char Decoration, unsigned int NumDeco)
{
	CalculateAlignment(Text, Decoration, NumDeco, ETextAlignment::ALIGN_Center);
}

void ConsoleRender::RightAlignment(string Text, char Decoration, unsigned int NumDeco)
{
	CalculateAlignment(Text, Decoration, NumDeco, ETextAlignment::ALIGN_Right);
}

void ConsoleRender::CalculateAlignment(string Text, char Decoration, unsigned int NumDeco, ETextAlignment Alignment)
{
	/* return if ConsoleCols is invalid*/
	if (ConsoleCols <= 0)
		return;

	/* number of total decoration text. it contains 'Decoration' and blank ' '. */
	int NumDecoText;
	/* Decoration Text. contains 'Decoration' chracter * NumDeco */
	string DecoText;
	bool bDecoEnable;

	/* load default decoration if param is non-valid and defulat is valid */
	if (Decoration == -1 && DefaultDecoration != -1)
		Decoration = DefaultDecoration;

	/* return Text if not use decoration */
	if (Decoration == -1 || NumDeco == 0)
	{
		NumDecoText = 0;
		bDecoEnable = false;
	}
	else
	{
		NumDecoText = 2 * NumDeco + 2;
		bDecoEnable = true;

		for (unsigned int i = 0; i < NumDeco; ++i)
			DecoText += Decoration;
	}



	/* calculate properties to write */
	SHORT NumRequiredLines = (SHORT)((((Text.length() - 1) / ConsoleCols + 1) * NumDecoText
		+ Text.length() - 1) / ConsoleCols + 1);
	int NumTextPerLine = ConsoleCols - NumDecoText;

	/* print text with left alignment */
	size_t strIdx = 0;
	for (int i = 0; i < NumRequiredLines; i = ++i, strIdx += NumTextPerLine)
	{
		if (strIdx < Text.length() + 1)
		{
			if (bDecoEnable == false)
			{
				cout << Text.substr(strIdx, NumTextPerLine) << "\n";
			}
			else
			{
				if (strIdx + NumTextPerLine < Text.length() + 1)
				{
					cout << DecoText << " " << Text.substr(strIdx, NumTextPerLine)
						<< " " << DecoText << "\n";
				}
				else
				{
					if (Alignment == ETextAlignment::ALIGN_Left)
					{
						size_t NumBlank = strIdx - (Text.length() - strIdx);
						string BlankText;
						for (int i = 0; i <= NumBlank; ++i)
							BlankText += ' ';

						cout << DecoText << " " << Text.substr(strIdx, NumTextPerLine)
							<< BlankText << DecoText << "\n";
					}
					else if (Alignment == ETextAlignment::ALIGN_Center)
					{
						size_t NumBlank = (strIdx - (Text.length() - strIdx)) / 2;
						string BlankText;
						for (int i = 0; i <= NumBlank; ++i)
							BlankText += ' ';

						cout << DecoText << BlankText << Text.substr(strIdx, NumTextPerLine)
							<< BlankText << DecoText << "\n";
					}
					else if (Alignment == ETextAlignment::ALIGN_Right)
					{
						size_t NumBlank = strIdx - (Text.length() - strIdx);
						string BlankText;
						for (int i = 0; i <= NumBlank; ++i)
							BlankText += ' ';

						cout << DecoText << BlankText << Text.substr(strIdx, NumTextPerLine)
							<< " " << DecoText << "\n";
					}
				}
			}
		}
	}

	CurrentLines += NumRequiredLines;
}

void ConsoleRender::SetDefaultDecoration(char InChanged)
{
	/* return if changed decoration is not valid */
	if (InChanged < 0)
		return;

	DefaultDecoration = InChanged;
}

void ConsoleRender::UpdateConsoleSize(SHORT InCols, SHORT InLines)
{
	/* return if params are not valid */
	if (InCols <= 0 || InLines <= 0)
		return;

	ConsoleCols = InCols;
	ConsoleLines = InLines;
}

bool ConsoleRender::Update(float DeltaTime)
{
	CurrentLines = 0;
	return false;
}





Console::Console(int Left, int Top, int Width, int Height)
	: ConsoleWHandle(GetConsoleWindow())
	, ConsoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
{
	/* deactives sync with c stdio library for performance */
	ios::sync_with_stdio(false);

	/* configures console properties */
	SetConsoleTitle(APP::DefaultConsoleTitle.c_str());
	SetWindowLong
	(
		ConsoleWHandle,
		GWL_STYLE,
		GetWindowLong(ConsoleWHandle, GWL_STYLE)
		& ~WS_MAXIMIZEBOX
		& ~WS_SIZEBOX
	);
	SetWindowSize(Left, Top, Width, Height);

	/* initializes using CONOSOLE_SCREEN_BUFFER_INFO */
	CONSOLE_SCREEN_BUFFER_INFOEX ScreenInfoEX;
	ScreenInfoEX.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(ConsoleHandle, &ScreenInfoEX);
	Cols = ScreenInfoEX.srWindow.Right - ScreenInfoEX.srWindow.Left + 1;
	Lines = ScreenInfoEX.srWindow.Bottom - ScreenInfoEX.srWindow.Top + 1;
	
	ScreenInfoEX.dwSize = { Cols, Lines };
	ScreenInfoEX.srWindow = { 0,0, Cols, Lines };
	ScreenInfoEX.dwMaximumWindowSize = { Cols, Lines };
	ScreenInfoEX.bFullscreenSupported = false;
	SetConsoleScreenBufferInfoEx(ConsoleHandle, &ScreenInfoEX);

	DWORD Mode;
	GetConsoleMode(ConsoleHandle, &Mode);
	Mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(ConsoleHandle, Mode);


	/* initialize ConsoleRender.*/
	uConsoleRender = std::unique_ptr<ConsoleRender>(new ConsoleRender(Cols, Lines));
}



void Console::SetWindowSize(int Left, int Top, int Width, int Height)
{
	if (ConsoleWHandle == nullptr)
		return;

	/* update window rect */
	MoveWindow(ConsoleWHandle, Left, Top, Width, Height, true);

	/* if remove this code, ShowScrollBar does not work sometimes.
	 * why this situation is occured? i dont know, but i know that
	 * it needs a little time interval between MoveWindow and Show
	 * ScrollBar functions. 
	 *
	 * in other words, it can be replaced by using 
	 * this_thread::sleep_for(chrono::miliseconds(10)), and so on. */
	UpdateWindow(ConsoleWHandle);
}