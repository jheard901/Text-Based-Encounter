#pragma once

#include "character.h"
//#include <stdint.h> //uint16_t

//found way to create unique ID here:
//http://stackoverflow.com/questions/14585385/best-practice-how-to-get-a-unique-identifier-for-the-object
//http://stackoverflow.com/questions/65524/unique-id-c
//http://stackoverflow.com/questions/1988679/algorithm-for-generating-a-unique-id-in-c

//when a team is first created they should randomly generate a unique ID that all their characters use to identify friendlys
class Team
{
private:
	Character* Pawn[4];	//max of four characters permitted on a team
	int teamSize;

	//unique id using union
	struct _ID
	{
		uint16_t i1;
		uint16_t i2;
		uint16_t i3;
		uint16_t i4;
	};

	union _keyID
	{
		_ID i;
		uint64_t id;
	};

	_keyID _myID;
public:
	//setup
	Team();
	Team(int size, int stats);	//size of team, and each character's stats
	~Team();
	void GenID();
	int GetID() const { return static_cast<int>(_myID.id); }	//returns ID of team; useful for differentiating what team players are on... I think
	//string GetName();	//future idea is to replace GetID() with this where applicable
	void InitTeam();

	//important functions
	void DisplayState();	//displays state of each character on team
	void TakeAction(Team* opposingTeam);	//gets action from each character on a team, to take against another team | this can be redone better later
	void CommitAction(Team* opposingTeam);
	bool IsTeamDefeated();	//true when all members have died
	void UpdateTeamState();	//updates the state of team setting Pawns dead/alive (in the future I will consider having these types of updates done immediately during the combat phase)
	void ResetCombatStatus();	//resets specific combat variables for Pawns to their defaults at the start of a combat phase
	Character* GetChar(int N) { return Pawn[N]; }	//returns a character by index
	Character* GetCharByID(int ID);	//returns a character by ID
	int GetTeamSize() { return teamSize; }
};