#pragma once
#include "Agent.h"
#include "Vector2.h"


class Decision
{
public:
	Decision(); //TODO Child decision class needs decision default constructor?
	Decision(Agent* owner) : m_owner(owner){};
	~Decision();
	Agent* m_owner;
	virtual void MakeDecision() = 0;
};


class BooleanDecision : public Decision
{
public:
	BooleanDecision();
	~BooleanDecision();

	bool value;
	Decision* trueDecision = nullptr; //runs if condition is true
	Decision* falseDecision = nullptr; // runs if conditions is false
	float m_timer;
	float cooldownTime;

};

//Sets agents 'timer' to length;
class SetTimeAction : Decision
{
public:
	SetTimeAction(float time) : m_length(time){};
	~SetTimeAction();

	float m_length;
	void makeDecision()
	{
		m_owner->m_timer = m_length;
	}
};

//Branches to another decision based on 'm_timer'
class CheckTimerDecision : BooleanDecision
{
public:
	CheckTimerDecision();
	~CheckTimerDecision();

	void makeDecision()
	{
		if (m_owner->m_timer < 0)
			trueDecision->MakeDecision();
		else
			falseDecision->MakeDecision();
	}
};


//Branches to another decision based on distance between 2 vectors
class CheckDistanceDecision : BooleanDecision //runs true if magnitude between owner.pos and target.pos is < distance
{
public:
	CheckDistanceDecision();
	~CheckDistanceDecision();

	float distance;

	void makeDecision()
	{
		if (Vector2((*m_owner).m_position - (*m_owner).m_target->m_position).Magnitude < distance)
			trueDecision->MakeDecision();
		else
			falseDecision->MakeDecision();
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
