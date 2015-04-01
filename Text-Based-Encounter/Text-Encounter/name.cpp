
#include "name.h"
#include "math.h"

GName::GName()
{
	numNames = 10;
	numTNames = 5;

	//create character names
	std::string* temp = new std::string[numNames];
	temp[0] = "Raphael";
	temp[1] = "Elizabeth";
	temp[2] = "Lucius";
	temp[3] = "Seigfried";
	temp[4] = "Edward";
	temp[5] = "Mirabelle";
	temp[6] = "Abraham";
	temp[7] = "Hildegard";
	temp[8] = "Fendrel";	//perhaps in the future could add in some way to store titles for a character | ex. Fendrel the Wicked
	temp[9] = "Ulric";

	//store them in the name vector
	for (int i = 0; i < numNames; i++)
	{
		nContainer.push_back(temp[i]);
	}

	//create team names
	std::string* tempT = new std::string[numTNames];
	tempT[0] = "Alpha";
	tempT[1] = "Beta";
	tempT[2] = "Charlie";
	tempT[3] = "Delta";
	tempT[4] = "Echo";

	//store them in the name vector
	for (int i = 0; i < numTNames; i++)
	{
		nTeamContainer.push_back(tempT[i]);
	}

	//delete our string arrays
	delete[] temp;
	delete[] tempT;
}

GName::~GName()
{

}

std::string GName::GetRandomName()
{
	if (!nContainer.empty())
	{
		int roll = math::GetTrueRandomInt(0, nContainer.size() - 1);
		std::string val = nContainer.at(roll);
		nContainer.erase(nContainer.begin() + roll);	//remove that name from container since it has been assigned
		return val;
	}
}

std::string GName::GetRandomTeamName()
{
	if (!nTeamContainer.empty())
	{
		int roll = math::GetTrueRandomInt(0, nTeamContainer.size() - 1);
		std::string val = nTeamContainer.at(roll);
		nTeamContainer.erase(nTeamContainer.begin() + roll);
		return val;
	}
}

