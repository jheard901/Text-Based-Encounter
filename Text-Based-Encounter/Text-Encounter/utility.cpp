
#include "utility.h"
#include <iostream>
#include <conio.h>	//kbhit()
#include <Windows.h>
#undef max	//to undefine the Windows max() macro as specified here: http://stackoverflow.com/questions/20446373/cin-ignorenumeric-limitsstreamsizemax-n-max-not-rrecognize-it
#pragma warning(disable : 4996) //gets rid of the buffer overflow warning as specified here: http://stackoverflow.com/questions/903064/compiler-error-function-call-with-parameters-that-may-be-unsafe

//I can't believe I'm using this method to clear
//the screen based off this: http://www.cplusplus.com/articles/4z18T05o/
//Changed it to use this other solution: http://stackoverflow.com/questions/6486289/how-can-i-clear-console
void ClearScreen()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
	SetConsoleCursorPosition(console, topLeft);
}

//this is suppose to be working but it is not, perhaps I am misinterpreting it and should
//be using one of the other topics located at the bottom to achieve the effect I am looking
//for: https://msdn.microsoft.com/en-us/library/windows/desktop/ms685118%28v=vs.85%29.aspx
void ScrollDown()
{
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//SMALL_RECT srcTargetWindow;
	//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	//POINT pt;
	int scrollLength = 20;

	//move down a lil bit
	for (int i = 0; i < scrollLength; i++) { std::cout << "\n"; }

	//GetConsoleScreenBufferInfo(console, &csbi);
	//if (csbi.srWindow.Top >= scrollLength)
	//{
	//	srcTargetWindow.Top = (SHORT)scrollLength;     // move top up
	//	srcTargetWindow.Bottom = -static_cast<SHORT>(scrollLength);  // move bottom up 
	//	srcTargetWindow.Left = 0;						// no change 
	//	srcTargetWindow.Right = 0;						// no change
	//
	//	SetConsoleWindowInfo(console, FALSE, &srcTargetWindow);
	//}

	//GetCursorPos(&pt);
	//COORD topLeft = { pt.x, pt.y - scrollLength };
	//SetConsoleCursorPosition(console, topLeft);
}

void Pause()
{
	std::cout << "\n\nPress enter to continue.\n";
	std::cin.get();
	std::cin.get();
}

int GetInt(int min, int max)
{
	bool ok = false;
	int in;

	while (!ok)
	{
		std::cin >> in;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number only: ";
		}
		else if (in < min || in > max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid number: ";
		}
		else
		{
			ok = true;
		}
	}
	return in;
}

//found some ideas on making this portable, but for now just testing it with Windows: http://stackoverflow.com/questions/1813552/tell-c-console-to-wait
void GSleep(float seconds)
{
	Sleep(DWORD(seconds * 1000));
}

//found info on how to make this effect from: http://www.cplusplus.com/reference/string/string/copy/
void DisplayString(std::string str)
{
	char* buffer = new char[str.size() + 1];
	str.copy(buffer, str.size(), 0);

	for (int i = 0; i < str.size(); i++)
	{
		std::cout << buffer[i];
		GSleep(0.05);
	}
	
	delete[] buffer;
}

//used this source to do this: http://www.cprogramming.com/fod/kbhit.html and https://msdn.microsoft.com/en-us/library/58w7c94c.aspx
//press any key to continue
void PressAnyKey()
{
	std::cout << "\n\nPress any key to continue...\n";

	while (1)
	{
		if (_kbhit())
		{
			_getch();
			break;
		}
	}
}