#pragma once

#include <stdint.h> //uint16_t

enum Controller { PLAYER, AI };
enum Action { ATTACK, DEFEND, CHARGE, FLEE };
enum State { NORMAL, DEFENDING, CHARGING, FLEEING };
enum Settings { DEFAULT, STRONG, OVERPOWERED };

class Character
{
private:
	//personal identifier
	struct _IDTag
	{
		uint16_t i1;
		uint16_t i2;
		uint16_t i3;
		uint16_t i4;
	};
	union _keyIDTag
	{
		_IDTag i;
		uint64_t id;
	};
	_keyIDTag _myID;

	//important elements
	typedef struct Stats
	{
		float Health;
		float AttackDmg;
		float CritChance;
		float CounterChance;
	};
	Stats stats;
	Stats cStats;	//current stats
	Controller controller;
	Action action;
	State state;
	Settings ini;

	float BASEHP, BASEATK, BASECRIT, BASECNTR;
	bool bInitialized;	//true when the character is ready/setup
public:
	//setup
	Character();
	Character(int settings);
	~Character();
	void GenID();
	int GetID() const { return static_cast<int>(_myID.id); }
	void InitCharacter(int controllerType, int initState);

	//charater actions
	void Attack(Character target);
	bool IsCriticalHit();
	void Defend();
	bool IsDefending();
	void CounterAttack(Character counterTarget);
	bool IsCounterAttack();
	void Charge();
	bool IsCharging();
	void Flee();
	bool IsFleeing();
	
	//affects character
	void DamageTaken(float dmgTaken);

	//retrieving or updating actions/states
	Action	GetAction();
	void	SetAction(Action newAction);
	State	GetState();
	void	SetState(State newState);

	//displays key info
	void DisplayStatus();
};