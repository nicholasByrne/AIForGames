#pragma once
#include "GameObject.h"

class Input;

class Player :	public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Update(float deltaTime);

	static Input* input;
};

