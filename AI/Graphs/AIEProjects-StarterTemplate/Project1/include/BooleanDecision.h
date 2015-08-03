#pragma once
#include "Decision.h"
#include "Vector2.h"

class BooleanDecision :	public Decision
{
public:
	BooleanDecision();
	~BooleanDecision();
};

//Sets agents 'timer' to length;
class SetTimeAction : Decision
{
public: 
	SetTimeAction();
	~SetTimeAction();

	float length;
	void makeDecision()
	{
		//owner.m_timer = length;
	}
};

//Branches to another decision based on 'm_timer'
class CheckTimerDecision : Decision
{
public:
	CheckTimerDecision();
	~CheckTimerDecision();

	Decision* trueDecision; //runs if condition is true
	Decision* falseDecision; // runs if conditions is false

	void makeDecision()
	{
		//if (owner.m_timer > 0)
		//	trueDecision->MakeDecision();
		//else
		//	falseDecision->MakeDecision();
	}
};


//Branches to another decision based on distance between 2 vectors
class CheckDistanceDecision : Decision
{
public:
	CheckDistanceDecision();
	~CheckDistanceDecision();

	float distance;
	Decision* trueDecision;
	Decision* falseDecision;

	void makeDecision()
	{
		//if (Vector2(owner.m_position - owner.target->m_position).Magnitude < distance)
		//	trueDecision->MakeDecision();
		//else
		//	falseDecision->MakeDecisoin();
	}
};


class WanderAction : Decision
{
public:
	WanderAction();
	~WanderAction();
	
	void MakeDecision();
};


class FleeAction : Decision
{
public:
	FleeAction();
	~FleeAction();
	void MakeDecision();
};
