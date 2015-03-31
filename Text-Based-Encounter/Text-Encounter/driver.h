#pragma once

#include "mode.h"

enum GameMode { DEFAULT_MODE, CHEAT_MODE };	//an idea further down the road

class GameDriver
{
private:
	bool bGameOver;
	int userInput;
	DefaultPlayMode* DPM;
public:
	GameDriver();
	~GameDriver();
	int GetInput(int min, int max);	//gets input from user within a specified range
	int ModeSelect();		//user selects game mode
	int DifficultySelect();	//user selects the difficulty mode
	int NetworkSelect();	//user selects network for multiplayer
	int TeamSelectA();		//user selects size of teams | in future, use better OOP method
	int TeamSelectB();
	void Init(int m, int d, int n, int a, int b);	//inits the game mode
	void Startup();
	void PlayGame();
	void Shutdown();
	void Run();

	//the main game functions
	void DisplayGameState();
	void GetAction();
	void Process();
	void UpdateGameState();
};
