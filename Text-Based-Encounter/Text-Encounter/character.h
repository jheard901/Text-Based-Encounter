#pragma once

#include "name.h"	//gives unique name ids to objects
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
	std::string name;

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
	float CRIT_MULTIPLIER;	//perhaps this should be added to stats?
	float CRIT_INCREMENT, COUNTER_INCREMENT;
	float FLEE_CHANCE;
	bool bAlive;
	bool bFlee;			//true when the character successfully fled during combat phase
	bool bAttacked;		//true when the character has taken dmg during the combat phase
	bool bCountered;	//true when the character has countered an attack
	bool bInitialized;	//true when the character is ready/setup
	bool bFinished;		//true when the character has successfully took action for their turn
	int atkTarget;		//the target to attack
	std::string atkTargetName;
	float cntrDmg;		//the damage inflicted by a counter attack

	//ai stuff
	typedef struct Threshold
	{
		float low;
		float mid;
		float high;
	};
	Threshold hp;
public:
	//setup
	Character();
	Character(int settings);
	~Character();
	void GenID();
	int GetID() const { return static_cast<int>(_myID.id); }
	void GenName();
	std::string GetName() { return name; }
	void InitCharacter(int controllerType, int initState);

	//charater actions
	void Attack(Character* target);
	bool IsCriticalHit();
	void Defend();
	bool IsDefending();
	void CounterAttack(Character* counterTarget);
	bool IsCounterAttack();
	void Charge();
	bool IsCharging();
	void Flee();
	bool IsFleeing(float chance);
	
	//affects character
	void DamageTaken(float dmgTaken, int srcPawnID, std::string srcPawnName);

	//retrieving or updating actions/states
	Action	GetAction();
	void	SetAction(Action newAction) { action = newAction; }
	Action	RetAction() { return action; }	//returns current action | diff from GetAction() so dont change this!
	State	GetState();
	void	SetState(int newState) { state = static_cast<State>(newState); }

	//checking if character has taken action
	void	SetFinished(bool bDone) { bFinished = bDone; }
	bool	IsFinished() { return bFinished; }

	//doing checks during the combat phase
	void SetDamaged(bool val) { bAttacked = val; }
	bool IsDamaged() { return bAttacked; }	//did char take dmg?
	void SetCountered(bool val) { bCountered = val; }
	bool Countered() { return bCountered; }	//did char counter?
	float GetCounterDmg() { return cntrDmg; }
	void SetFlee(bool val) { bFlee = val; }
	bool FleeSuccess() { return bFlee; }

	//handling crit/counter/flee chance
	void ResetCrit() { cStats.CritChance = stats.CritChance; }
	void ResetCounter() { cStats.CounterChance = stats.CounterChance; }
	void IncreaseCrit(float val) { cStats.CritChance += val; }
	void IncreaseCounter(float val) { cStats.CounterChance += val; }
	float GetCritIncrement() { return CRIT_INCREMENT; }
	float GetCntrIncrement() { return COUNTER_INCREMENT; }
	float GetFleeChance() { return FLEE_CHANCE; }
	float GetCritChance() { return cStats.CritChance; }
	float GetCounterChance() { return cStats.CounterChance; }

	//setting attack target
	void	SetTarget(int targetID, std::string targetName) { atkTarget = targetID; atkTargetName = targetName; }
	int		GetTarget() { return atkTarget; }
	std::string GetTargetName() { return atkTargetName; }

	//ai stuff
	float AssessTarget(Character* target);
	float AssessAction(Character* target, Action myAction);
	Action PickBestAction(Character* target);
	float GetHPLow() { return hp.low; }
	float GetHPMid() { return hp.mid; }
	float GetHPHigh() { return hp.high; }

	//reset specific combat variables
	void	ResetCombat();

	//key info
	void DisplayStatus();
	void DisplayStatusShort();
	Controller GetController() { return controller; }
	void SetAlive(bool val) { bAlive = val; }
	bool IsAlive() { return bAlive; }
	float GetHealth() { return cStats.Health; }
};