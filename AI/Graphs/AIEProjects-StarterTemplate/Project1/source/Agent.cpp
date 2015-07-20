#include "Agent.h"
#include "IBehaviour.h"

Agent::Agent()
{

}


Agent::~Agent()
{

}


void Agent::Update(float deltaTime)
{
	//iterator
	std::list<IBehaviour*>::iterator iter;
	//Sensing

	//Thinking
		//Add or remove behaviours from m_behaviours list

	
	//Acting
	for (iter = m_behaviours.begin(); iter != m_behaviours.end(); ++iter)
	{
		(*iter)->Update(this, deltaTime);
	}

}


void Agent::Draw()
{

}


void Agent::AddBehaviour(IBehaviour* a_behaviour)
{
	m_behaviours.push_back(a_behaviour);
}