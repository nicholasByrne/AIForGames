#pragma once
#include <list>
#include <string>
#include <iostream>
#include "Decision.h" //Yay??

class Agent;

enum BehaviourResult { Success, Failure, Pending };

//Base Behaviour class
class IBehaviour
{
public:
	IBehaviour();
	~IBehaviour();

	float m_weight;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime) = 0;
};

//Base class for 'Sequence' and 'Selector' nodes
class Composite : public IBehaviour
{
public:
	Composite();
	~Composite();

	std::list<IBehaviour*> m_childBehaviours;
	IBehaviour* m_child;
	IBehaviour* m_pendingChild = nullptr;
	int pendingChildIndex = 0;
	BehaviourResult result;
	virtual BehaviourResult Update(Agent* pAgent, float deltaTime) = 0;
	void AddChild(IBehaviour* child)
	{
		m_childBehaviours.push_back(child);
	}

};

//'AND' node for running a list of behaviours consecutively until one fails
class Sequence : public Composite
{
public:
	Sequence();
	~Sequence();

	BehaviourResult Update(Agent* pAgent, float deltaTime)
	{		
		for (std::list<IBehaviour*>::iterator iter = m_childBehaviours.begin(); iter != m_childBehaviours.end(); ++iter)
		{
			if (m_pendingChild != nullptr && (*iter) != m_pendingChild)
			{
				continue; //until we get to pending child
			}

			m_pendingChild = nullptr;
			result = (*iter)->Update(pAgent, deltaTime);

			if (result == Failure)
			{
				return Failure;
			}
			else if (result == Pending)
			{
				m_pendingChild = (*iter);
				return Pending;
			}
		}
		return Success;
	}
};

//'OR' node for running a list of behaviours until one succeeds 
class Selector : public Composite
{
public:
	Selector();
	~Selector();

	BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		for (std::list<IBehaviour*>::iterator iter = m_childBehaviours.begin(); iter != m_childBehaviours.end(); ++iter)
		{
			if (m_pendingChild != nullptr && (*iter) != m_pendingChild)
			{
				continue;
			}

			m_pendingChild = nullptr;
			result = (*iter)->Update(pAgent, deltaTime);

			if (result == Success)
			{
				return Success;
			}
			else if (result == Pending)
			{
				m_pendingChild = (*iter);
				return Pending;
			}
		}
		return Failure;
	}
};

//Inverts the result of its child Behaviour
class InverseDecorator : public IBehaviour
{
public:
	InverseDecorator();
	~InverseDecorator();

	IBehaviour* m_child;
	BehaviourResult result;

	BehaviourResult Update(Agent* pAgent, float deltaTime)
	{
		result = m_child->Update(pAgent, deltaTime);
		switch (result)
		{
		case Success: 
			return Failure;
		case Failure:
			return Success;
		}
	}
};


class LogDecorator : public IBehaviour
{
	LogDecorator();
	~LogDecorator();

	IBehaviour* m_child;
	std::string m_message;

	BehaviourResult Update(Agent* pAgent, float deltaTime)
	{ 
		//TODO print somewhere useful (like in game), make a function to change message?
		std::cout << m_message;
		return m_child->Update(pAgent, deltaTime);
	}
};