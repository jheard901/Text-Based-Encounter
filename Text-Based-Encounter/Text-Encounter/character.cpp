
#include "character.h"
#include "math.h"
#include "utility.h"
#include <iostream>
#include <math.h>	//round()

Character::Character() : bAlive(true)
{
	ini = DEFAULT;	//default character settings
	GenID();
	GenName();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
	CRIT_MULTIPLIER = 3;
	CRIT_INCREMENT = 50;
	COUNTER_INCREMENT = 25;
	FLEE_CHANCE = 20;
}

Character::Character(int settings) : bAlive(true)
{
	ini = static_cast<Settings>(settings);
	GenID();
	GenName();

	//base stat settings
	BASEHP = 600;
	BASEATK = 60;
	BASECRIT = 10;
	BASECNTR = 5;
	CRIT_MULTIPLIER = 3;
	CRIT_INCREMENT = 50;
	COUNTER_INCREMENT = 25;
	FLEE_CHANCE = 20;
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

void Character::GenName()
{
	//name = new std::string(GName::Inst().GetRandomName());	//this results in name showing only the address in memory when used with cout
	name = GName::Inst().GetRandomName();
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

	//set ai stuff
	hp.high = stats.Health * 0.75;
	hp.mid = stats.Health * 0.5;
	hp.low = stats.Health * 0.25;
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
	target->DamageTaken(float(damage), GetID(), GetName());
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

bool Character::IsFleeing(float chance)
{
	float roll = frn() * 100;

	if (roll <= chance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//this is where we check what state the character is in, and respond accordingly based off that
void Character::DamageTaken(float dmgTaken, int srcPawnID, std::string srcPawnName)
{
	switch (state)
	{
	//full damage taken
	case(NORMAL) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetName(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	//half damage taken and possible for a counter attack
	case(DEFENDING) :
		cStats.Health -= round(dmgTaken * 0.5);
		DisplayString("\nPawn "); std::cout << GetName(); DisplayString(" was defending and only took "); std::cout << round(dmgTaken * 0.5); DisplayString(" damage.");
		if (IsCounterAttack())
		{
			DisplayString("\nPawn "); std::cout << GetName(); DisplayString(" landed a counter attack and inflicted "); std::cout << dmgTaken; DisplayString(" damage back!");
			SetCountered(true);
			cntrDmg = dmgTaken;
			ResetCounter();
		}
		break;
	//full damage taken
	case(CHARGING) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetName(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	//full damage taken
	case(FLEEING) :
		cStats.Health -= dmgTaken;
		SetDamaged(true);
		DisplayString("\nPawn "); std::cout << GetName(); DisplayString(" took "); std::cout << dmgTaken; DisplayString(" damage.");
		break;
	}
}

Action Character::GetAction()
{
	//PLAYER gets visual output
	if (controller == PLAYER)
	{
		std::cout << "\nPawn " << GetName() << " - Your Actions:";
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

//heuristic for measuring the value of a target | this could be done better to account
//for the AI's own HP in regards to the damage that is likely to be inflicted by a charcater;
//additionally, this is biased towards picking a target based off who the AI should attack
//and not accounting for all other possible actions such as defending, charging, or fleeing
float Character::AssessTarget(Character* target)
{
	float value = 1;

	//is alive
	if (target->IsAlive())
	{
		value += 10;

		//assess health
		if (target->GetHealth() > target->GetHPHigh())
		{
			value += 20;
		}
		else if (target->GetHealth() < target->GetHPHigh() && target->GetHealth() > target->GetHPMid())
		{
			value += 40;
		}
		else if (target->GetHealth() < target->GetHPMid() && target->GetHealth() > target->GetHPLow())
		{
			value += 60;
		}
		else if (target->GetHealth() < target->GetHPLow())
		{
			value += 100;
		}

		//assess defense
		if (target->GetCounterChance() > 50)
		{
			value += 10;
		}
		else
		{
			value += 40;
		}
	}

	return value;
}

//this could be done so much better like I recommended with AssessTarget, but I am
//short on time to get this done, so this will have to do for now
float Character::AssessAction(Character* target, Action myAction)
{
	float value = 1;

	switch (myAction)
	{
	case(ATTACK) :
		//assess my health
		if (GetHealth() > GetHPHigh())
		{
			value += 300;
		}
		else if (GetHealth() < GetHPHigh() && GetHealth() > GetHPMid())
		{
			value += 200;
		}
		else if (GetHealth() < GetHPMid() && GetHealth() > GetHPLow())
		{
			value += 150;
		}
		else if (GetHealth() < GetHPLow())
		{
			value += 50;
		}
		//assess target health (higher chance if their health is low)
		if (target->GetHealth() > target->GetHPHigh())
		{
			value += 75;
		}
		else if (target->GetHealth() < target->GetHPHigh() && target->GetHealth() > target->GetHPMid())
		{
			value += 125;
		}
		else if (target->GetHealth() < target->GetHPMid() && target->GetHealth() > target->GetHPLow())
		{
			value += 175;
		}
		else if (target->GetHealth() < target->GetHPLow())
		{
			value += 300;
		}
		//assess target counter chance
		if (target->GetCounterChance() > 75)
		{
			value -= 300;
		}
		else if (target->GetCounterChance() < 75 && target->GetCounterChance() > 50)
		{
			value -= 200;
		}
		else if (target->GetCounterChance() < 50 && target->GetCounterChance() > 20)
		{
			value += 150;
		}
		else if (target->GetCounterChance() < 20)
		{
			value += 100;
		}
		//compare my health to target health
		if (GetHealth() > target->GetHealth())
		{
			value += 200;
		}
		else if (GetHealth() <= target->GetHealth())
		{
			value += 100;
		}
		//assess my crit chance
		if (GetCritChance() > 75)
		{
			value += 350;
		}
		else if (GetCritChance() > 50)
		{
			value += 250;
		}
		else if (GetCritChance() > 25)
		{
			value += 150;
		}
		else
		{
			value += 100;
		}
		break;
	case(DEFEND) :
		//assess my health (higher chance here if health is low)
		if (GetHealth() > GetHPHigh())
		{
			value += 50;
		}
		else if (GetHealth() < GetHPHigh() && GetHealth() > GetHPMid())
		{
			value += 100;
		}
		else if (GetHealth() < GetHPMid() && GetHealth() > GetHPLow())
		{
			value += 250;
		}
		else if (GetHealth() < GetHPLow())
		{
			value += 400;
		}
		//compare my health to target health
		if (GetHealth() > target->GetHealth())
		{
			value += 50;
		}
		else if (GetHealth() <= target->GetHealth())
		{
			value += 100;
		}
		//assess my counter chance
		if (GetCounterChance() > 75)
		{
			value += 250;
		}
		else if (GetCounterChance() < 75 && GetCounterChance() > 50)
		{
			value += 200;
		}
		else if (GetCounterChance() < 50 && GetCounterChance() > 20)
		{
			value += 150;
		}
		else if (GetCounterChance() < 20)
		{
			value += 50;
		}
		//assess target crit chance
		if (target->GetCritChance() > 50)
		{
			value += 150;
		}
		else
		{
			value += 100;
		}
		break;
	case(CHARGE) :
		//assess my health
		if (GetHealth() > GetHPHigh())
		{
			value += 250;
		}
		else if (GetHealth() < GetHPHigh() && GetHealth() > GetHPMid())
		{
			value += 200;
		}
		else if (GetHealth() < GetHPMid() && GetHealth() > GetHPLow())
		{
			value += 100;
		}
		else if (GetHealth() < GetHPLow())
		{
			value += 50;
		}
		//assess my crit chance
		if (GetCritChance() >= 50)
		{
			value += 50;
		}
		else
		{
			value += 150;
		}
		//assess my counter chance
		if (GetCounterChance() > 75)
		{
			value += 10;
		}
		else if (GetCounterChance() < 75 && GetCounterChance() > 50)
		{
			value += 50;
		}
		else if (GetCounterChance() < 50 && GetCounterChance() > 20)
		{
			value += 175;
		}
		else if (GetCounterChance() < 20)
		{
			value += 250;
		}
		break;
	case(FLEE) :
		//assess my health (higher chance here if health is low)
		if (GetHealth() > GetHPHigh())
		{
			value += 50;
		}
		else if (GetHealth() < GetHPHigh() && GetHealth() > GetHPMid())
		{
			value += 100;
		}
		else if (GetHealth() < GetHPMid() && GetHealth() > GetHPLow())
		{
			value += 250;
		}
		else if (GetHealth() < GetHPLow())
		{
			value += 400;
		}
		//assess target health
		if (target->GetHealth() > target->GetHPHigh())
		{
			value += 50;
		}
		else if (target->GetHealth() < target->GetHPHigh() && target->GetHealth() > target->GetHPMid())
		{
			value += 100;
		}
		else if (target->GetHealth() < target->GetHPMid() && target->GetHealth() > target->GetHPLow())
		{
			value += 150;
		}
		else if (target->GetHealth() < target->GetHPLow())
		{
			value += 200;
		}
		break;
	}

	if (value <= 0) { value = 1; }	//safety net
	return value;
}

//picks the best action against a target
Action Character::PickBestAction(Character* target)
{
	const int numActions = 4;
	float hValue[numActions];	//represents four heuristic values | one for each action
	float bestValue = 0;
	int action;

	//assess each action against target
	for (int i = 0; i < numActions; i++)
	{
		hValue[i] = AssessAction(target, static_cast<Action>(i));	//the best value basically means that character is the most favorable target
		if (hValue[i] > bestValue)
		{
			bestValue = hValue[i];
			action = i;
		}
	}

	//do a little RNG magic to make sure it is not always guaranteed to pick the same move
	float accumulatedWeight = 0;
	float normalizedWeight[numActions];
	float weightCount = 0;
	float randValue = frn();
	for (int i = 0; i < numActions; i++)
	{
		accumulatedWeight += hValue[i];
	}
	for (int i = 0; i < numActions; i++)
	{
		normalizedWeight[i] = hValue[i] / accumulatedWeight;
	}
	//method 1
	//for (int i = 0; i < numActions; i++)
	//{
	//	if (normalizedWeight[i] + weightCount >= randValue)
	//	{
	//		action = i;
	//		break;
	//	}
	//	else
	//	{
	//		weightCount += normalizedWeight[i];
	//	}
	//}
	//method 2
	int j = 0;
	while (1)
	{
		if (normalizedWeight[j] >= frn())
		{
			action = j;
			break;
		}
		else
		{
			j++;
		}
		if (j >= numActions) { j = 0; }
	}

	return static_cast<Action>(action);
}

//resets specific combat variables only at the beginning of the combat phase
void Character::ResetCombat()
{
	bFlee = false;
	bAttacked = false;
	bCountered = false;
}

void Character::DisplayStatus()
{
	std::cout << "\nPawn " << GetName();
	std::cout << "\nHP: " << cStats.Health;
	std::cout << "\nAttack Pwr: " << cStats.AttackDmg;
	std::cout << "\nCrit Chance: " << cStats.CritChance;
	std::cout << "\nCounter Chance: " << cStats.CounterChance;
}

void Character::DisplayStatusShort()
{
	std::cout << "\nPawn " << GetName();
	std::cout << "\nHP: " << cStats.Health;
	std::cout << "\nCounter Chance: " << cStats.CounterChance;
}
