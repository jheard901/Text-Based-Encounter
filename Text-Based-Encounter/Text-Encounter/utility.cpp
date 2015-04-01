
#include "utility.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) // TODO: Move this to a generic all-in-one win/linux define in a header somewhere
#include <Windows.h>
    #ifdef max
        #undef max
    #endif
#endif

namespace utility {


void ClearScreen()
{
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) 
    std::system("cls");
#else // Assume posix (kinda sloppy, but oh well)
    std::system("clear");
#endif
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
void GSleep(const int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

//found info on how to make this effect from: http://www.cplusplus.com/reference/string/string/copy/
void DisplayString(const std::string& str)
{
    for(auto const& character : str)
    {
        std::cout << character;
        GSleep(50);
    }
}

void PressAnyKey()
{
	std::cout << "\n\nPress any key to continue...\n";

#if defined(WIN32) || defined(WIN64) || defined(_WIN32)
        system("pause");
#else
        system("read");
#endif
}
};
