#pragma once
#include <list>

class Agent;
enum BehaviourResult { Success, Failure, Running };

class IBehaviour
{
public:
	IBehaviour();
	~IBehaviour();

	virtual void Update(Agent* pAgent, float deltaTime) = 0;
};

//Base class for 'Sequence' and 'Selector' nodes
class Composite : IBehaviour
{
	Composite();
	~Composite();

	std::list<IBehaviour*> m_childBehaviours;
	IBehaviour* m_pendingChild;

	virtual void Update(Agent* pAgent, float deltaTime) = 0;

};

//'AND' node for running a list of behaviours consecutively until one fails
class Sequence : Composite
{
	Sequence();
	~Sequence();

	void Update(Agent* pAgent, float deltaTime)
	{
		//foreach child in childBehaviours
		//	if child.execute(agent) == Failure
		//		return Failure
		//return Success
	}
};

//'OR' node for running a list of behaviours until one succeeds 
class Selector : Composite
{
	Selector();
	~Selector();

	void Update(Agent* pAgent, float deltaTime)
	{
		//foreach child in childBehaviours
		//	if child.execute(agent) == Success
		//		return Success
		//return Failure

		

	}
};