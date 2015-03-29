
#include "utility.h"
#include <iostream>
#include <string>

//I can't believe I'm using this method to clear
//the screen based off this: http://www.cplusplus.com/articles/4z18T05o/
void ClearScreen()
{
	std::cout << std::string(100, '\n');
}

void Pause()
{
	std::cout << "\n\nPress enter to continue.\n";
	std::cin.get();
	std::cin.get();
}