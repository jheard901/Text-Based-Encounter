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
	void InitTeam();

	//important functions
	void DisplayState();	//displays state of each character on team
	int GetTeamSize() { return teamSize; }

};