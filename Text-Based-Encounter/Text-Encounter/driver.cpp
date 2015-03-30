
#include "driver.h"
#include "utility.h"
#include <iostream>
#include <stdlib.h> //srand(), rand()
#include <time.h> //time()

#define NEW_LINE(x) { for(int i = 0; i < x; i++) { std::cout << std::endl; } }	//quick macro for new lines
const int LEN = 2;
const int SEC = 2;

//some handy info on strings (in case I need them later)
// http://stackoverflow.com/questions/5838711/c-cin-input-with-spaces
// http://www.cplusplus.com/reference/string/
// http://www.cplusplus.com/reference/string/string/
// http://stackoverflow.com/questions/191757/c-concatenate-string-and-int

GameDriver::GameDriver()
{
	
}

GameDriver::~GameDriver()
{
	Shutdown();
}

int GameDriver::GetInput(int min, int max)
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

int GameDriver::ModeSelect()
{
	std::cout << "\nSelect the user mode: \n";
	std::cout << "Single-Player = 0\n";
	std::cout << "Multiplayer = 1\n";
	userInput = GetInput(0, 1);

	//check if input is valid; if so, return it. If not, repeat asking for input

	return userInput;
}

int GameDriver::DifficultySelect()
{
	std::cout << "\nSelect skill level: \n";
	std::cout << "Normal = 0\n";
	std::cout << "Hard = 1\n";
	std::cout << "Overpowered = 2\n";
	userInput = GetInput(0, 2);

	return userInput;
}

//this is an idea for later, since I know a lil bit of net coding
int GameDriver::NetworkSelect()
{
	std::cout << "\nSelect network to use: \n";
	std::cout << "Local = 0\n";
	std::cout << "Online = 1\n";
	std::cout << "Offline = 2\n";
	userInput = GetInput(0, 2);

	return userInput;
}

void GameDriver::Init(int m, int d, int n)
{
	//seed random number generator once
	srand(unsigned(time(NULL)));

	//create game mode (this game for now only has one)
	DPM = new DefaultPlayMode;

	//setup the player mode
	DPM->SetPlayerMode(m);

	//setup difficulty
	DPM->SetDifficulty(d);

	//setup mutliplayer network connection
	DPM->SetConnection(n);


}

void GameDriver::Startup()
{
	//need to dynamically create the mode object based off input from ModeSelect()
	int mode = ModeSelect();
	int difficulty = DifficultySelect();
	int network = NetworkSelect();

	//Initialize game based off selected settings
	Init(mode, difficulty, network);
}

void GameDriver::PlayGame()
{
	////////////////////////////////////////////
	// PreGame Run Once
	////////////////////////////////////////////
	if (!DPM->IsGameStarted())
	{
		//run any pregame code here
		DPM->InitGame();
		ClearScreen();

		//game is starting!
		std::cout << "NEW BATTLE ENCOUNTER";
		NEW_LINE(LEN);

		//then notify game is starting
		DPM->SetGameStarted(1);
	}

	if (DPM->IsGameStarted())
	{
		////////////////////////////////////////////
		// The Main Game Loop
		////////////////////////////////////////////
		while (!DPM->IsGameOver())
		{
			DisplayGameState();
			PressAnyKey();
			//this should notify users of the current situation (i.e. Each team character's HP, Crit/Counter Chance)

			GetAction();
			//this should notify the user of all actions they can do, then proceed to get input for what their action will be

			Process();
			//this should display what happens as the result of the player's action
			//this includes displaying damage taken/inflicted, defending, etc... by both Team characters

			UpdateGameState();
			PressAnyKey();
			//this should check for win/loss conditions and set if the game has concluded or not depending on what happened in Process()
			//update any other things that were not addressed earlier here as well
		}
	}
	
}

void GameDriver::Shutdown()
{

}

void GameDriver::Run()
{
	Startup();
	ClearScreen();
	PlayGame();
	Pause();
}

//this should notify users of the current situation (i.e. Each team character's HP, Crit/Counter Chance)
void GameDriver::DisplayGameState()
{
	DPM->Alpha->DisplayState();
	NEW_LINE(LEN);
	DPM->Beta->DisplayState();
	NEW_LINE(LEN);
}

//this should notify the user of all actions they can do, then proceed to get input for what their action will be
//set each character's state accordingly as well
void GameDriver::GetAction()
{
	std::cout << "\nACTION PHASE\n";
	DPM->ActionPhase();
	//DPM->Alpha->TakeAction();
	//NEW_LINE(LEN);
	//DPM->Beta->TakeAction();
	//NEW_LINE(LEN);
}

//this should display what happens as the result of the player's action
//this includes displaying damage taken/inflicted, defending, etc... by both Team characters
void GameDriver::Process()
{
	std::cout << "\nCOMBAT PHASE\n";
	DPM->CombatPhase();
}

//this should check for win/loss conditions and set if the game has concluded or not depending on what happened in Process()
//update any other things that were not addressed earlier here as well
void GameDriver::UpdateGameState()
{
	DPM->UpdateGameState();
}

