
#include "character.h"
#include "math.h"
#include <iostream>

Character::Character()
{
	ini = DEFAULT;	//default character settings
	GenID();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
}

Character::Character(int settings)
{
	ini = static_cast<Settings>(settings);
	GenID();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
}

Character::~Character()
{

}

void Character::GenID()
{
	_myID.i.i1 = GetRandomInt(0, 9);
	_myID.i.i2 = GetRandomInt(0, 9);
	_myID.i.i3 = GetRandomInt(0, 9);
	_myID.i.i4 = GetRandomInt(0, 9);
}

//controller 0 = PLAYER, 1 = AI | initState should be 0 (NORMAL)
void Character::InitCharacter(int controllerType, int initState)
{
	//setup stats cap
	switch (ini)
	{
	case(DEFAULT) :
		stats.Health = BASEHP;
		stats.AttackDmg = BASEATK;
		stats.CritChance = BASECRIT;
		stats.CounterChance = BASECNTR;
		break;
	case(STRONG) :
		stats.Health = BASEHP * 1.5;
		stats.AttackDmg = BASEATK * 1.25;
		stats.CritChance = BASECRIT * 2.5;
		stats.CounterChance = BASECNTR * 2;
		break;
	case(OVERPOWERED) :
		stats.Health = BASEHP * 2;
		stats.AttackDmg = BASEATK * 2;
		stats.CritChance = BASECRIT * 5;
		stats.CounterChance = BASECNTR * 5;
		break;
	}

	//set current stats
	cStats.Health = stats.Health;
	cStats.AttackDmg = stats.AttackDmg;
	cStats.CritChance = stats.CritChance;
	cStats.CounterChance = stats.CounterChance;

	controller = static_cast<Controller>(controllerType);
	state = static_cast<State>(initState);
}

void Character::DisplayStatus()
{
	std::cout << "\nPawn " << GetID() << ":";
	std::cout << "\nHP: " << cStats.Health;
	std::cout << "\nAttack Pwr: " << cStats.AttackDmg;
	std::cout << "\nCrit Chance: " << cStats.CritChance;
	std::cout << "\nCounter Chance: " << cStats.CounterChance;
}

