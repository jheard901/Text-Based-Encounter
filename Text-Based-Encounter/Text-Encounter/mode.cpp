
#include "mode.h"
#include "math.h"
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

void Mode::SetGameStarted(bool value)
{
	bGameStarted = value;
}

void Mode::SetGameOver(bool value)
{
	bGameOver = value;
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

void DefaultPlayMode::ActionPhase()
{
	//I would for loop here counting by using teamsize as
	//the limiter and going through each team (via array)
	//in the future
	Alpha->TakeAction(Beta);
	std::cout << "\n\n";
	Beta->TakeAction(Alpha);
	std::cout << "\n\n";
}

void DefaultPlayMode::CombatPhase()
{
	//picking a team to go first is decided randomly ("Team x has first strike!" is outputted)
	int rPick = GetTrueRandomInt(0, 1);
	Alpha->ResetCombatStatus();
	Beta->ResetCombatStatus();

	//Team Alpha goes first
	if (rPick == 0)
	{
		std::cout << "\nTeam " << Alpha->GetName() << " has first strike!\n";
		Alpha->CommitAction(Beta);
		std::cout << "\n\n";
		std::cout << "\nTeam " << Beta->GetName() << " begins to act!\n";
		Beta->CommitAction(Alpha);
		std::cout << "\n\n";
	}
	//or team Beta goes first
	else
	{
		std::cout << "\nTeam " << Beta->GetName() << " has first strike!\n";
		Beta->CommitAction(Alpha);
		std::cout << "\n\n";
		std::cout << "\nTeam " << Alpha->GetName() << " begins to act!\n";
		Alpha->CommitAction(Beta);
		std::cout << "\n\n";
	}
}

void DefaultPlayMode::UpdateGameState()
{
	Alpha->UpdateTeamState();
	Beta->UpdateTeamState();

	//check all possible ending states
	if (Alpha->DidTeamFlee() || Beta->DidTeamFlee())
	{
		std::cout << "\nA team has escaped and the encounter ends in a draw!";
		SetGameOver(true);
	}
	else if (Alpha->IsTeamDefeated() && !Beta->IsTeamDefeated())
	{
		std::cout << "\nTeam " << Beta->GetName() << " is victorious!\n";
		SetGameOver(true);
	}
	else if (!Alpha->IsTeamDefeated() && Beta->IsTeamDefeated())
	{
		std::cout << "\nTeam " << Alpha->GetName() << " is victorious!\n";
		SetGameOver(true);
	}
	else if (Alpha->IsTeamDefeated() && Beta->IsTeamDefeated())
	{
		std::cout << "\nBoth teams have died. It's a draw!";
		SetGameOver(true);
	}
	else
	{
		//both teams are still alive then
	}
}