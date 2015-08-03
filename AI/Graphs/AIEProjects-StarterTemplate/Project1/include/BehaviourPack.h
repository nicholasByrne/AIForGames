#pragma once
#include "IBehaviour.h"
#include "Agent.h"
#include "Vector2.h"
#include <list>
#include <algorithm>
#include <vector>

class Seek : public IBehaviour
{
public:
	Seek(Vector2* targetPos) : m_targetPos(targetPos){};
	Seek(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	~Seek();

	Vector2* m_targetPos;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//Apply seek force to pAgent
		Vector2 m_toTarget = Vector2::Normalise(*m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity;
		pAgent->AddForce( (m_toTarget) * 1000.0f) ;
	}
};


class Flee : public IBehaviour
{
public:
	Flee(Vector2* targetPos) : m_targetPos(targetPos){};
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
public:
	Vector2 m_previousTarget;
	virtual void Update(float f_radius, float f_distance, float f_jitter)
	{

	}
};


class Pursue : public IBehaviour
{
public:
	Pursue(Vector2* targetPos, Vector2* targetVelocity) : m_targetPos(targetPos), m_targetVelocity(targetVelocity){};
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
public:
	Evade(Vector2* targetPos, Vector2* targetVelocity) : m_targetPos(targetPos), m_targetVelocity(targetVelocity){};
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
public:
	Arrive(Vector2* targetPos, float arriveRadius) : m_targetPos(targetPos), m_arriveRadius(arriveRadius){};
	Arrive(Agent& targetAgent, float arriveRadius) : m_targetPos(&targetAgent.m_position), m_arriveRadius(arriveRadius){};
	~Arrive();

	Vector2* m_targetPos;
	float m_arriveRadius;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//direction and distance to target
		Vector2 direction = (Vector2::Normalise(*m_targetPos - pAgent->m_position));
		float distance = Vector2::Distance(pAgent->m_position, *m_targetPos);

		//seek force to target
		Vector2 force((*m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity);

		//scalar representing distance from target (1 = radius edge, 0 = target, else > 1)
		float scalar = fmin(distance / m_arriveRadius, 1);

		//if within radius
		if (scalar < 1)
		{
			//scale seek force down according to distance
			force *= scalar;
			//(-1, 1) scalar how close heading is with direction to target
			float dot = Vector2::Dot(direction, Vector2::Normalise(pAgent->m_velocity));
			
			//force to slow down when approaching target
			Vector2 resistance = -1 * (Vector2::Normalise(pAgent->m_velocity)) * Vector2::Magnitude(pAgent->m_velocity) * dot * 10;

			//add resistance
			force += resistance;
		}

		//add force to pAgent
		pAgent->AddForce(force - pAgent->m_velocity);
	}

};


//Avoid
class Avoid : public IBehaviour
{
public:
	Avoid(float maxSeeDist, float maxAvoidForce, std::vector<GameObject*>& objectVector) : m_maxSeeDistance(maxSeeDist), m_maxAvoidForce(maxAvoidForce), m_objectVector(&objectVector){};
	~Avoid();

	float m_maxSeeDistance;
	float m_maxAvoidForce;
	std::vector<GameObject*>* m_objectVector;
	Vector2 ahead;
	Vector2 ahead2;
	virtual void Update(Agent* pAgent, float deltaTime)
	{
		//how far ahead is "seen"
		float dynamicLength = pAgent->m_velocity.Magnitude() / pAgent->m_maxVelocity;
		ahead = Vector2(pAgent->m_position + (Vector2::Normalise(pAgent->m_velocity) * dynamicLength));
		ahead2 = Vector2(pAgent->m_position + (Vector2::Normalise(pAgent->m_velocity) * dynamicLength * 0.5f));

		//find closest(biggest) threat // collision detection Line + circle?
		GameObject* biggestThreat = nullptr;
		float biggestThrestDist;
		for (int i = 0; i < m_objectVector->size(); i++)
		{
			//TODO MAKE LINE COLLISION?
			bool collision = GameObject::CheckCollision(ahead, (*m_objectVector)[i]);
			//if collision = true, and not previous threat || is closer than previous threat
			if ((collision == true) && ((Vector2::Distance(pAgent->m_position, (*m_objectVector)[i]->m_position) < biggestThrestDist) || biggestThreat == nullptr))
			{
				biggestThreat = (*m_objectVector)[i];
			}
		}

		Vector2 avoidanceForce(0, 0);
		if (biggestThreat != nullptr)
		{
			avoidanceForce = ahead - biggestThreat->m_position;
			avoidanceForce.NormaliseThis();
			avoidanceForce * m_maxAvoidForce;
		}
		//TODO v fix this? v
		pAgent->AddForce(avoidanceForce);
	}
};

//Idle?

class AttackAction : IBehaviour
{

};