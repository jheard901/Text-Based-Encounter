#pragma once

#include <vector>
#include <string>

//name generator
class GName
{
private:
	int numNames;	//character names
	int numTNames;	//team names
	std::vector<std::string> nContainer;
	std::vector<std::string> nTeamContainer;
public:
	GName();
	static GName &Inst() { static GName GNameVX3000; return GNameVX3000; }
	~GName();

	//std::string GetSpecificName(int element); <- if we wanted to get a specific name from the list
	std::string GetRandomName();		//returns a random character name
	std::string GetRandomTeamName();	//returns random team name
};

