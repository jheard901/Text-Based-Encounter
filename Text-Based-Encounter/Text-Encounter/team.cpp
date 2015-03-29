
#include "team.h"
#include "math.h"
#include <iostream>

Team::Team() : teamSize(0)
{
	GenID();
}

//quickly creates team of specified size with specified stats - skipping the need to InitTeam()
Team::Team(int size, int stats) : teamSize(0)
{
	GenID();
	for (int i = 0; i < size; i++)
	{
		Pawn[i] = new Character(stats);
		teamSize++;
	}
}

Team::~Team()
{

}

void Team::GenID()
{
	_myID.i.i1 = GetRandomInt(0, 9);
	_myID.i.i2 = GetRandomInt(0, 9);
	_myID.i.i3 = GetRandomInt(0, 9);
	_myID.i.i4 = GetRandomInt(0, 9);
}

void Team::InitTeam()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			std::cout << "\nTeam " << GetID() << " Pawn " << Pawn[i]->GetID() << ": Player(0) or AI(1)?\n";
			int cSelector;
			std::cin >> cSelector;
			Pawn[i]->InitCharacter(cSelector, 0);
		}
	}
}

void Team::DisplayState()
{
	std::cout << "\nTeam " << GetID() << ":\n";
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			Pawn[i]->DisplayStatus();
			std::cout << "\n";
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}