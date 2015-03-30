#pragma once

#include <string>

//for use with console applications only...
//and windows only in its current state...
void ClearScreen();
void ScrollDown();
void Pause();
int GetInt(int min, int max);	//used for quickly getting a valid int between a min and max
void GSleep(float seconds);
void DisplayString(std::string str);
void PressAnyKey();	//proceeds based off any key down
