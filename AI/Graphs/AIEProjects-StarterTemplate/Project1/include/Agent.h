#pragma once
#include <list>
#include "Vector2.h"
#include "GameObject.h"

class IBehaviour;

class Agent : public GameObject
{
public:
	Agent();
	Agent(Vector2& startingPos, Texture* texture, SpriteBatch* spriteBatch);
	virtual ~Agent();

	virtual void Update(float deltaTime);
	//virtual void Draw();

	void AddBehaviour(IBehaviour* a_behaviour);
	//Agent* m_targetAgent;
protected:
	std::list<IBehaviour*> m_behaviours;
	//Agent* m_targetAgent;
};


