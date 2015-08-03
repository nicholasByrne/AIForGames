#pragma once
#include "Agent.h"

class Decision
{
public:
	Decision();
	~Decision();

	virtual void MakeDecision() = 0;
};

