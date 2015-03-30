//Text-Based Encounter
//
//Created by Javier Heard
//3-27-15
//
//Consider adding in functionality for the case that
//only AI controllers are playing; make some way to allow users
//to step through each turn so they can watch the encounter
//as it happens.

#include "driver.h"
#include <iostream>
#include <Windows.h>

void SetupConsole();

int main()
{
	SetupConsole();
	GameDriver TextGame;
	TextGame.Run();
	return 0;
}

//resizing the console source: http://www.3dbuzz.com/forum/threads/102195-How-do-you-resize-a-console-window-in-C
//enables scrolling with mouse wheel | Source: http://stackoverflow.com/questions/4687745/how-to-enable-scrollable-console
void SetupConsole()
{
	//setting console size | Note: this is measured by rows/columns, not pixels!
	const int WIDTH = 90;
	const int HEIGHT = 30;

	//setting the buffer size | Note: setting this disables using the scrollbar if it is set too small (using 800 x 600 is default for the buffer)
	const int BUFFER_WIDTH = 400;
	const int BUFFER_HEIGHT = 800;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_SMALL_RECT size;
	DWORD mode;
	_COORD coord;

	size.Top = 0;
	size.Left = 0;
	size.Right = WIDTH - 1;
	size.Bottom = HEIGHT - 1;
	coord.X = BUFFER_WIDTH;
	coord.Y = BUFFER_HEIGHT;
	
	//setting buffer and window size
	SetConsoleScreenBufferSize(hConsole, coord);
	SetConsoleWindowInfo(hConsole, TRUE, &size);

	//enabling mouse scrolling
	GetConsoleMode(hConsole, &mode);
	SetConsoleMode(hConsole, mode & ~ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT);
}