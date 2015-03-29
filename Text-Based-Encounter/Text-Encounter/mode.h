#pragma once

#include "team.h"

enum PlayerMode { SINGLE_PLAYER, MULTIPLAYER };
enum Difficulty { EASY, HARD, OP };
enum Connection { LOCAL, ONLINE, OFFLINE };

class Mode
{
protected:
	bool bGameStarted, bGameOver;
public:
	Mode();
	~Mode();
	void SetGameStarted(int value);
	void SetGameOver(int value);
	bool IsGameStarted();
	bool IsGameOver();

};

//the mode should define all the information needed to play the base game experience (including SP, MP)
class DefaultPlayMode : public Mode
{
private:
	PlayerMode pMode;
	Difficulty pSkill;
	Connection pNetwork;

	bool bGameOver;
public:
	Team* Alpha;	//this will be the player's team by default
	Team* Beta;

	DefaultPlayMode();
	DefaultPlayMode(int mode);
	~DefaultPlayMode();
	void SetPlayerMode(int pm);
	void SetDifficulty(int pd);
	void SetConnection(int pc);

	void InitGame();	//setup the game rules prior to calling this
};

//future modes can be added for different experiences apart from the text-based combat of DefaultPlayMode
//such as an adventure mode where you explore areas, and then have combat encounters depending on what areas
//you explore

