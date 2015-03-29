
#include "mode.h"
#include <iostream>

////////////////////////////////////////////
// Mode Base Class
////////////////////////////////////////////

Mode::Mode() : 
	bGameStarted(false), bGameOver(false)
{

}

Mode::~Mode()
{

}

// 0 = false, 1 = true
void Mode::SetGameStarted(int value)
{
	if (value == 0) { bGameStarted = false; }
	else { bGameStarted = true; }
}

//0 = false, 1 = true
void Mode::SetGameOver(int value)
{
	if (value == 0) { bGameOver = false; }
	else { bGameOver = true; }
}

bool Mode::IsGameStarted()
{
	if (bGameStarted == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Mode::IsGameOver()
{
	if (bGameOver == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

////////////////////////////////////////////
// DefaultPlayMode Class
////////////////////////////////////////////

DefaultPlayMode::DefaultPlayMode()
{

}

DefaultPlayMode::DefaultPlayMode(int mode)
{

}

DefaultPlayMode::~DefaultPlayMode()
{

}

void DefaultPlayMode::SetPlayerMode(int pm)
{
	pMode = static_cast<PlayerMode>(pm);
}

void DefaultPlayMode::SetDifficulty(int pd)
{
	pSkill = static_cast<Difficulty>(pd);
}

void DefaultPlayMode::SetConnection(int pc)
{
	pNetwork = static_cast<Connection>(pc);
}

void DefaultPlayMode::InitGame()
{
	//should probably have some way to choose the number of teams/characters added in object-oriented later
	switch (pMode)
	{
	case(SINGLE_PLAYER) :
		switch (pSkill)
		{
		case(EASY) :
			Alpha = new Team(1, EASY);
			Beta = new Team(1, EASY);
			break;
		case(HARD) :
			Alpha = new Team(1, EASY);
			Beta = new Team(1, HARD);
			break;
		case(OP) :
			Alpha = new Team(1, HARD);
			Beta = new Team(1, OP);
			break;
		}
		break;
	case(MULTIPLAYER) :
		switch (pNetwork)
		{
		case(LOCAL) :
			break;
		case(ONLINE) :
			break;
		case(OFFLINE) :
			break;
		}
		break;
	}
	
	//init the team's characters; later consider adding in the ability for user's to customize each character from within the InitTeam() call
	//perhaps I could add a parameter called 'gmode' which would be an int that automatically inits the settings based off the mode enums
	Alpha->InitTeam();
	Beta->InitTeam();
}