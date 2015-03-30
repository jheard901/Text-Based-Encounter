
#include "team.h"
#include "math.h"
#include "utility.h"
#include <iostream>
#include <vector>

Team::Team() : teamSize(0)
{
	GenID();
	GenName();
}

//quickly creates team of specified size with specified stats - skipping the need to InitTeam()
Team::Team(int size, int stats) : teamSize(0)
{
	GenID();
	GenName();
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

void Team::GenName()
{
	name = GName::Inst().GetRandomTeamName();
}

void Team::InitTeam()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			std::cout << "\nTeam " << GetName() << " Pawn " << Pawn[i]->GetName() << ": Player(0) or AI(1)?\n";
			Pawn[i]->InitCharacter(GetInt(0, 1), 0);
		}
	}
}

void Team::DisplayState()
{
	std::cout << "\nTeam " << GetName() << ":\n";
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

void Team::TakeAction(Team* opposingTeam)
{
	std::cout << "\nTeam " << GetName() << ":\n";
	if (GetTeamSize() > 0)	//use IsEmpty() as a shortcut for this in future updates
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			Pawn[i]->SetFinished(false);
			while (!Pawn[i]->IsFinished())
			{
				//this is how the player takes action
				if (Pawn[i]->GetController() == PLAYER)
				{
					Pawn[i]->SetAction(Pawn[i]->GetAction());

					//attacking requires a little extra work
					if (Pawn[i]->RetAction() == ATTACK)
					{
						//store each possible target
						std::vector<int> charID;
						std::vector<std::string> charName;

						//display all targets and their status
						std::cout << "\nSelect Target:";
						for (int j = 0; j < opposingTeam->GetTeamSize(); j++)
						{
							std::cout << "\nTeam " << opposingTeam->GetName();
							opposingTeam->GetChar(j)->DisplayStatusShort();
						}

						//display list of targetst o select
						std::cout << "\n\nTarget List:";
						for (int j = 0; j < opposingTeam->GetTeamSize(); j++)
						{
							std::cout << "\nPawn " << opposingTeam->GetChar(j)->GetName() << " = " << j;
							charID.push_back(opposingTeam->GetChar(j)->GetID());
							charName.push_back(opposingTeam->GetChar(j)->GetName());
						}

						std::cout << "\n\nYour Selection: ";
						int value = GetInt(0, charID.size() - 1);
						Pawn[i]->SetTarget(charID.at(value), charName.at(value));
					}

					//set state based off action
					Pawn[i]->SetState(static_cast<int>(Pawn[i]->RetAction()));

					//conclude this character's turn
					Pawn[i]->SetFinished(true);
					std::cout << "\n";
				}
				//this is how AI takes action
				else if (Pawn[i]->GetController() == AI)
				{
					//AI does some action here (need to make a function for it in character.cpp)
					//maybe add in some feedback like: "Pawn selected an action" once AI has chosen
				}
			}
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

void Team::CommitAction(Team* opposingTeam)
{
	std::cout << "\nTeam " << GetName() << ":\n";
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{

			//notify user pawn is dead
			if (!Pawn[i]->IsAlive())
			{
				DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" is dead!");
			}
			//otherwise proceed as normal
			else
			{
				//the meat of processing occurs in this area here
				switch (Pawn[i]->RetAction())
				{
				case(ATTACK) :
					DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" attempts to attack Pawn "); std::cout << Pawn[i]->GetTargetName() << std::endl;
					Pawn[i]->Attack(opposingTeam->GetCharByID(Pawn[i]->GetTarget()));
					if (opposingTeam->GetCharByID(Pawn[i]->GetTarget())->Countered())
					{
						Pawn[i]->DamageTaken(opposingTeam->GetCharByID(Pawn[i]->GetTarget())->GetCounterDmg(), Pawn[i]->GetID(), Pawn[i]->GetName());
						opposingTeam->GetCharByID(Pawn[i]->GetTarget())->SetCountered(false);
					}
					break;
				case(DEFEND) :
					DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" is defending.");
					break;
				case(CHARGE) :
					DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" is attempting to charge up.");
					if (Pawn[i]->IsDamaged())
					{
						Pawn[i]->IncreaseCrit(Pawn[i]->GetCritIncrement() * 0.5);
						Pawn[i]->IncreaseCounter(Pawn[i]->GetCntrIncrement() * 0.5);
						DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" took damage this turn and only partially charged.");
					}
					else
					{
						Pawn[i]->IncreaseCrit(Pawn[i]->GetCritIncrement());
						Pawn[i]->IncreaseCounter(Pawn[i]->GetCntrIncrement());
						DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" successfully charged!");
					}
					break;
				case(FLEE) :
					DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" is attempting to flee combat!");
					//lower chance to flee if damaged
					if (Pawn[i]->IsDamaged())
					{
						DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" took damage this turn and is less mobile.");
						if (Pawn[i]->IsFleeing(Pawn[i]->GetFleeChance() * 0.5))
						{
							Pawn[i]->SetFlee(true);
							DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" successfully escaped from combat!");
						}
						else
						{
							DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" failed to escape.");
						}
					}
					//higher flee chance if not hurt
					else
					{
						if (Pawn[i]->IsFleeing(Pawn[i]->GetFleeChance()))
						{
							Pawn[i]->SetFlee(true);
							DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" successfully escaped from combat!");
						}
						else
						{
							DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" failed to escape.");
						}
					}
					break;
				}
			}
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

bool Team::DidTeamFlee()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			if (Pawn[i]->FleeSuccess())
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

bool Team::IsTeamDefeated()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			if (Pawn[i]->IsAlive())
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

void Team::UpdateTeamState()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			//check if pawn has died
			if (Pawn[i]->GetHealth() <= 0)
			{
				if (Pawn[i]->IsAlive())
				{
					Pawn[i]->SetAlive(false);
					DisplayString("\nPawn "); std::cout << Pawn[i]->GetName(); DisplayString(" died this turn.");
				}
			}
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

void Team::ResetCombatStatus()
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			Pawn[i]->ResetCombat();
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}

Character* Team::GetCharByID(int ID)
{
	if (GetTeamSize() > 0)
	{
		for (int i = 0; i < GetTeamSize(); i++)
		{
			if (Pawn[i]->GetID() == ID)
			{
				return Pawn[i];
			}
		}
	}
	else
	{
		std::cout << "\nError. TeamSize is <= 0.";
	}
}