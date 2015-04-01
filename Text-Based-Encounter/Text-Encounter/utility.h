#pragma once

#include <string>

namespace utility 
{

    //for use with console applications only...
    //and windows only in its current state...
    void ClearScreen();
    void ScrollDown();
    void Pause();
    int GetInt(int min, int max);	//used for quickly getting a valid int between a min and max
    void GSleep(const int milliseconds);
    void DisplayString(const std::string& str);
    void PressAnyKey();	//proceeds based off any key down
};
