#include "Console.h"
#include <iostream>



void ConsoleRender::FillLine(char Character)
{
	if (ConsoleCols <= 0)
		return;

	string Content;
	for (int i = 0; i < ConsoleCols; ++i)
		Content += Character;
	
	cout << Content << "\n";
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
	size_t NumLines = (((Text.length() - 1) / ConsoleCols + 1) * NumDecoText
		+ Text.length() - 1) / ConsoleCols + 1;
	int NumTextPerLine = ConsoleCols - NumDecoText;

	/* print text with left alignment */
	size_t strIdx = 0;
	for (int i = 0; i < NumLines; i = ++i, strIdx += NumTextPerLine)
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
}

bool ConsoleRender::Update()
{
	return false;
}





Console::Console(int Left, int Top, int Width, int Height)
	: ConsoleWHandle(GetConsoleWindow())
	, ConsoleHandle(GetStdHandle(STD_OUTPUT_HANDLE))
{
	/* deactive sync with c stdio library for performance */
	ios::sync_with_stdio(false);



	/* get console screen buffer's informations and initialize class members */
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	GetConsoleScreenBufferInfo(ConsoleHandle, &ScreenInfo);
	Cols = ScreenInfo.srWindow.Right - ScreenInfo.srWindow.Left + 1;
	Lines = ScreenInfo.srWindow.Bottom - ScreenInfo.srWindow.Top + 1;

	/* initialize ConsoleRender */
	pConsoleRender = std::unique_ptr<ConsoleRender>(new ConsoleRender(Cols, Lines));

	/* configure console window size */
	SetWindowSize(Left, Top, Width, Height);

	
	/* remove console scroll bar */
	ShowScrollBar(ConsoleWHandle, SB_BOTH, FALSE);
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