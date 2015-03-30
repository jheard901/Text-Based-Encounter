
#include "character.h"
#include "math.h"
#include "utility.h"
#include <iostream>
#include <math.h>	//round()

Character::Character() : bAlive(true)
{
	ini = DEFAULT;	//default character settings
	GenID();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
	CRIT_MULTIPLIER = 3;
	CRIT_INCREMENT = 50;
	COUNTER_INCREMENT = 25;
}

Character::Character(int settings) : bAlive(true)
{
	ini = static_cast<Settings>(settings);
	GenID();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
	CRIT_MULTIPLIER = 3;
	CRIT_INCREMENT = 50;
	COUNTER_INCREMENT = 25;
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

void Character::Attack(Character* target)
{
	//calculate some damage
	int damage = GetRandomInt(cStats.AttackDmg, cStats.AttackDmg * 1.2);

	//check if it crits
	if (IsCriticalHit())
	{
		DisplayString("\nIt's a critical hit!");
		damage *= CRIT_MULTIPLIER;
		ResetCrit();
	}

	//inflict that damage to the target
	target->DamageTaken(float(damage), GetID());
}

bool Character::IsCriticalHit()
{
	float roll = frn() * 100;

	if (roll <= cStats.CritChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Character::IsCounterAttack()
{
	float roll = frn() * 100;

	if (roll <= cStats.CounterChance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//this is where we check what state the character is in, and respond accordingly based off that
void Character::DamageTaken(float dmgTaken, int srcPawnID)
{
	switch (state)
	{
	//full damage taken
	case(NORMAL) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetID(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	//half damage taken and possible for a counter attack
	case(DEFENDING) :
		cStats.Health -= round(dmgTaken * 0.5);
		DisplayString("\nPawn "); std::cout << GetID(); DisplayString(" was defending and only took "); std::cout << round(dmgTaken * 0.5); DisplayString(" damage.");
		if (IsCounterAttack())
		{
			DisplayString("\nPawn "); std::cout << GetID(); DisplayString(" landed a counter attack and inflicted "); std::cout << dmgTaken; DisplayString(" damage back!");
			SetCountered(true);
			cntrDmg = dmgTaken;
			ResetCounter();
		}
		break;
	//full damage taken
	case(CHARGING) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetID(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	//full damage taken
	case(FLEEING) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetID(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	}
}

Action Character::GetAction()
{
	//PLAYER gets visual output
	if (controller == PLAYER)
	{
		std::cout << "\nPawn " << GetID() << " - Your Actions:";
		std::cout << "\nAttack = 0";
		std::cout << "\nDefend = 1";
		std::cout << "\nCharge = 2";
		std::cout << "\nFlee = 3";
		std::cout << "\nSelect an action: ";
		int iAction = GetInt(0, 3);
		return static_cast<Action>(iAction);
	}
	//AI should automatically choose (no visual output)
	else if (controller == AI)
	{
		//maybe throw in a function here for the AI (it's gonna be long I imagine)
	}
}

//resets specific combat variables only at the beginning of the combat phase
void Character::ResetCombat()
{
	bAttacked = false;
	bCountered = false;
}

void Character::DisplayStatus()
{
	std::cout << "\nPawn " << GetID() << ":";
	std::cout << "\nHP: " << cStats.Health;
	std::cout << "\nAttack Pwr: " << cStats.AttackDmg;
	std::cout << "\nCrit Chance: " << cStats.CritChance;
	std::cout << "\nCounter Chance: " << cStats.CounterChance;
}

