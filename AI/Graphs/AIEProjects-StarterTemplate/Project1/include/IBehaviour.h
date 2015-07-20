#pragma once

class Agent;

class IBehaviour
{
public:
	IBehaviour();
	~IBehaviour();

	virtual void Update(Agent* pAgent, float deltaTime) = 0;
};


