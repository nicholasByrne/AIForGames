#pragma once
#include "IBehaviour.h"
#include "Agent.h"
#include "Vector2.h"
#include <list>
#include <algorithm>
#include <vector>

class SeekBehaviour : public IBehaviour
{
public:
	SeekBehaviour(Vector2* targetPos) : m_targetPos(targetPos){};
	SeekBehaviour(Vector2* targetPos, float weight) : m_targetPos(targetPos), m_weight(weight){}; //TODO add cpp for initialisations
	SeekBehaviour(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	SeekBehaviour(Agent& targetAgent, float weight) : m_targetPos(&targetAgent.m_position), m_weight(weight){};
	~SeekBehaviour();

	Vector2* m_targetPos;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//Apply seek force to pAgent
		Vector2 toTarget = Vector2::Normalise(*m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity;
		pAgent->m_force += (toTarget* 1000.0f);
		//pAgent->AddForce(toTarget * 1000.0f);
		return Success;
	}
};


class FleeBehaviour : public IBehaviour
{
public:
	FleeBehaviour(Vector2* targetPos) : m_targetPos(targetPos){};
	FleeBehaviour(Agent& targetAgent) : m_targetPos(&targetAgent.m_position){};
	~FleeBehaviour();

	Vector2* m_targetPos;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//Apply flee force to pAgent
		Vector2 m_fromTarget = Vector2::Normalise(pAgent->m_position - *m_targetPos) * pAgent->m_maxVelocity;
		pAgent->m_force += m_fromTarget - pAgent->m_velocity;
		return Success;
	}
};


class WanderBehaviour : public IBehaviour //TODO Wander
{
public:
	Vector2 m_previousTarget;
	virtual BehaviourResult Update(float f_radius, float f_distance, float f_jitter)
	{

	}
};


class PursueBehaviour : public IBehaviour
{
public:
	PursueBehaviour(Vector2* targetPos, Vector2* targetVelocity) : m_targetPos(targetPos), m_targetVelocity(targetVelocity){};
	PursueBehaviour(Agent& targetAgent) : m_targetPos(&targetAgent.m_position), m_targetVelocity(&targetAgent.m_velocity){};
	~PursueBehaviour();

	Vector2* m_targetPos;
	Vector2* m_targetVelocity;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//apply purse force to pAgent
		Vector2 direction = (*m_targetPos + *m_targetVelocity) - pAgent->m_position;
		pAgent->m_force += Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity;
		return Success;
	}
};


class EvadeBehaviour : public IBehaviour
{
public:
	EvadeBehaviour(Vector2* targetPos, Vector2* targetVelocity) : m_targetPos(targetPos), m_targetVelocity(targetVelocity){};
	EvadeBehaviour(Agent& targetAgent) : m_targetPos(&targetAgent.m_position), m_targetVelocity(&targetAgent.m_velocity){};
	~EvadeBehaviour();

	Vector2* m_targetPos;
	Vector2* m_targetVelocity;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//apply evade force to pAgent
		Vector2 direction = -1 * ((*m_targetPos + *m_targetVelocity) - pAgent->m_position);
		pAgent->m_force += Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity;
		return Success;
	}
};


class ArriveBehaviour : public IBehaviour
{
public:
	ArriveBehaviour(Vector2* targetPos, float arriveRadius) : m_targetPos(targetPos), m_arriveRadius(arriveRadius){};
	ArriveBehaviour(Agent& targetAgent, float arriveRadius) : m_targetPos(&targetAgent.m_position), m_arriveRadius(arriveRadius){};
	~ArriveBehaviour();

	Vector2* m_targetPos;
	float m_arriveRadius;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
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
		pAgent->m_force += force - pAgent->m_velocity;
		return Success;
	}

};


//Avoid
class AvoidBehaviour : public IBehaviour
{
public:
	AvoidBehaviour(std::vector<Agent*>& objectVector, float maxSeeDist, float maxAvoidForce) : m_objectVector(&objectVector), m_maxSeeDistance(maxSeeDist), m_maxAvoidForce(maxAvoidForce){};
	~AvoidBehaviour();

	float m_maxSeeDistance;
	float m_maxAvoidForce;
	std::vector<Agent*>* m_objectVector;
	Vector2 ahead;
	Vector2 ahead2;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//how far ahead is "seen"
		float dynamicLength = pAgent->m_velocity.Magnitude() / pAgent->m_maxVelocity;
		ahead = Vector2(pAgent->m_position + (Vector2::Normalise(pAgent->m_velocity) * dynamicLength));
		ahead2 = Vector2(pAgent->m_position + (Vector2::Normalise(pAgent->m_velocity) * dynamicLength * 0.5f));

		//find closest(biggest) threat // collision detection Line + circle?
		GameObject* biggestThreat = nullptr;
		float biggestThrestDist = std::numeric_limits<float>::max();

		for (int i = 0; i < m_objectVector->size(); i++)
		{
			//TODO MAKE LINE COLLISION?
			bool collision = GameObject::CheckCollision(ahead, (*m_objectVector)[i]);
			//if collision = true, and not previous threat || is closer than previous threat
			if ((collision == true) && biggestThreat == nullptr)
			{
				biggestThreat = (*m_objectVector)[i];
				biggestThrestDist = Vector2::Distance(pAgent->m_position, biggestThreat->m_position);
			}
			else if ((collision == true) && ((Vector2::Distance(pAgent->m_position, (*m_objectVector)[i]->m_position) < biggestThrestDist)));
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
		pAgent->m_force += avoidanceForce;
		return Success;
	}
};

//Idle?

class AttackBehaviour : public IBehaviour
{

};


class CheckDistanceBehaviour : public IBehaviour
{

};


class CheckTimerBehaviour : public IBehaviour
{

};

class SetTimerBehaviour : public IBehaviour
{

};