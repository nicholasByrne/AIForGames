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
	SeekBehaviour(Vector2& targetPos);
	SeekBehaviour(Vector2& targetPos, float weight);
	SeekBehaviour(Agent& targetAgent);
	SeekBehaviour(Agent& targetAgent, float weight);
	~SeekBehaviour();

	Vector2 m_targetPos;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//Apply seek force to pAgent
		Vector2 toTarget = Vector2::Normalise(m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity;
		pAgent->m_force += (toTarget* 1000.0f) * m_weight;
		//pAgent->AddForce(toTarget * 1000.0f);
		return Success;
	}
};


class FleeBehaviour : public IBehaviour
{
public:
	FleeBehaviour(Vector2& targetPos);
	FleeBehaviour(Vector2& targetPos, float weight);
	FleeBehaviour(Agent& targetAgent);
	FleeBehaviour(Agent& targetAgent, float weight);
	~FleeBehaviour();

	Vector2 m_targetPos;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//Apply flee force to pAgent
		Vector2 m_fromTarget = Vector2::Normalise(pAgent->m_position - m_targetPos) * pAgent->m_maxVelocity;
		pAgent->m_force += (m_fromTarget - pAgent->m_velocity) * m_weight;
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
	PursueBehaviour(Agent& targetAgent);
	PursueBehaviour(Agent& targetAgent, float weight);
	PursueBehaviour(Vector2& targetPos, Vector2& targetVelocity);
	PursueBehaviour(Vector2& targetPos, Vector2& targetVelocity, float weight);
	~PursueBehaviour();

	Vector2 m_targetPos;
	Vector2 m_targetVelocity;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//apply purse force to pAgent
		Vector2 direction = (m_targetPos + m_targetVelocity) - pAgent->m_position;
		pAgent->m_force += (Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity) * m_weight;
		return Success;
	}
};


class EvadeBehaviour : public IBehaviour
{
public:
	EvadeBehaviour(Agent& targetAgent);
	EvadeBehaviour(Agent& targetAgent, float weight);
	EvadeBehaviour(Vector2& targetPos, Vector2& targetVelocity);
	EvadeBehaviour(Vector2& targetPos, Vector2& targetVelocity, float weight);
	~EvadeBehaviour();

	Vector2 m_targetPos;
	Vector2 m_targetVelocity;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//apply evade force to pAgent
		Vector2 direction = -1 * ((m_targetPos + m_targetVelocity) - pAgent->m_position);
		pAgent->m_force += (Vector2::Normalise(direction) * pAgent->m_maxVelocity - pAgent->m_velocity) * m_weight;
		return Success;
	}
};


class ArriveBehaviour : public IBehaviour
{
public:
	ArriveBehaviour(Agent& targetAgent, float arriveRadius);
	ArriveBehaviour(Agent& targetAgent, float arriveRadius, float weight);
	ArriveBehaviour(Vector2& targetPos, float arriveRadius);
	ArriveBehaviour(Vector2& targetPos, float arriveRadius, float weight);
	~ArriveBehaviour();

	Vector2 m_targetPos;
	float m_arriveRadius;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		//direction and distance to target
		Vector2 direction = (Vector2::Normalise(m_targetPos - pAgent->m_position));
		float distance = Vector2::Distance(pAgent->m_position, m_targetPos);

		//seek force to target
		Vector2 force((m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity);

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
		pAgent->m_force += (force - pAgent->m_velocity) * m_weight;
		return Success;
	}

};


//Avoid
class AvoidBehaviour : public IBehaviour
{
public:
	AvoidBehaviour(float maxSeeDist, float maxAvoidForce);
	AvoidBehaviour(std::vector<Agent*>& objectVector, float maxSeeDist, float maxAvoidForce, float weight);
	~AvoidBehaviour();

	float m_maxSeeDistance, m_maxAvoidForce;
	std::vector<Agent*>* m_objectVector;
	Vector2 ahead, ahead2;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		m_objectVector = CollisionManager::Get()->GetGameObjectVector();
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
		pAgent->m_force += (avoidanceForce) * m_weight;
		return Success;
	}
};

//Idle?

class AttackBehaviour : public IBehaviour
{
public:
};


class CheckDistanceBehaviour : public IBehaviour //Returns true if (pAgent.pos - pAgent.target.pos).magnitude < distance
{
public:
	CheckDistanceBehaviour(float distance);
	CheckDistanceBehaviour(float distance, float weight);
	~CheckDistanceBehaviour();

	float m_distance;

	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		if (Vector2(pAgent->m_position - pAgent->m_target->m_position).Magnitude() < m_distance)
		{
			return Success;
		}
		return Failure;
	}
};


class CheckTimerBehaviour : public IBehaviour
{
public:
	CheckTimerBehaviour(float weight);
	~CheckTimerBehaviour();

	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		if (pAgent->m_timer < 0)
		{
			return Success;
		}
		return Failure;
	}
};

class SetTimerBehaviour : public IBehaviour
{
public:
	SetTimerBehaviour(float time);
	SetTimerBehaviour(float time, float weight);
	~SetTimerBehaviour();

	float m_length;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		pAgent->m_timer = m_length;
		return Success;
	}
};


class SeekPathBehaviour : public IBehaviour
{
public:
	SeekPathBehaviour();
	SeekPathBehaviour(float weight);
	~SeekPathBehaviour();

	Vector2 m_targetPos;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		if (pAgent->m_path.empty() == true)
		{
			return Failure;
		}
		m_targetPos = *pAgent->m_path.begin();
		//Apply seek force to pAgent
		Vector2 toTarget = Vector2::Normalise(m_targetPos - pAgent->m_position) * pAgent->m_maxVelocity;
		//pAgent->m_force += (toTarget* 1000.0f) * m_weight;
		pAgent->AddForce(toTarget * 1000.0f);
			
		//if within (20) pixels
			if (Vector2::MagnitudeSqrd(m_targetPos - pAgent->m_position) < 400 && pAgent->m_path.size() > 1)
		{
			pAgent->m_path.pop_front();
		}
		return Success;
	}
};