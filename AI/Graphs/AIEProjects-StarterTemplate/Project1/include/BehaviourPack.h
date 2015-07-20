#pragma once
#include "IBehaviour.h"
#include "Agent.h"
#include "Vector2.h"
#include <list>


class Seek : public IBehaviour
{
	Seek(Vector2& targetPos) : m_targetPos(&targetPos){};
	Seek(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	~Seek();

	Vector2* m_targetPos;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//Apply seek force to pAgent
		Vector2 m_toTarget = Vector2::Normalise(*m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity;
		pAgent->AddForce(m_toTarget - pAgent->m_velocity);
	}
};


class Flee : public IBehaviour
{
	Flee(Vector2& targetPos) : m_targetPos(&targetPos){};
	Flee(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	~Flee();

	Vector2* m_targetPos;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//Apply flee force to pAgent
		Vector2 m_fromTarget = Vector2::Normalise(pAgent->m_position - *m_targetPos) * pAgent->m_maxVelocity;
		pAgent->AddForce(m_fromTarget - pAgent->m_velocity);
	}
};


class Wander : public IBehaviour //TODO Wander
{
	Vector2 m_previousTarget;
	virtual void Update(float f_radius, float f_distance, float f_jitter)
	{

	}
};


class Pursue : public IBehaviour
{
	Pursue(Vector2& targetPos, Vector2& targetVelocity) : m_targetPos(&targetPos), m_targetVelocity(&targetVelocity){};
	Pursue(Agent targetAgent) : m_targetPos(&targetAgent.m_position), m_targetVelocity(&targetAgent.m_velocity){};
	~Pursue();

	Vector2* m_targetPos;
	Vector2* m_targetVelocity;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//apply purse force to pAgent
		Vector2 direction = (*m_targetPos + *m_targetVelocity) - pAgent->m_position;
		pAgent->AddForce(Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity);
	}
};


class Evade : public IBehaviour
{
	Evade(Vector2& targetPos, Vector2& targetVelocity) : m_targetPos(&targetPos), m_targetVelocity(&targetVelocity){};
	Evade(Agent& targetAgent) : m_targetPos(&targetAgent.m_position), m_targetVelocity(&targetAgent.m_velocity){};
	~Evade();

	Vector2* m_targetPos;
	Vector2* m_targetVelocity;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//apply evade force to pAgent
		Vector2 direction = (*m_targetPos - *m_targetVelocity) - pAgent->m_position;
		pAgent->AddForce(Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity);
	}
};


class Arrive : public IBehaviour
{
	Arrive(Vector2& targetPos) : m_targetPos(&targetPos){};
	Arrive(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	~Arrive();

	Vector2* m_targetPos;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//direction and distance to target
		Vector2 direction = (Vector2::Normalise(*m_targetPos - pAgent->m_position));
		float distance = Vector2::Distance(pAgent->m_position, *m_targetPos);

		//seek force to target
		pAgent->AddForce((*m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity);

		//scalar representing distance from target (1 = radius edge, 0 = target, else > 1)

	}

};

//Avoid