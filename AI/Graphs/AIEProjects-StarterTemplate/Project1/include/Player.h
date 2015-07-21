#pragma once
#include "Agent.h"

class Input;

class Player :	public Agent
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);

	static Input* input;
};

