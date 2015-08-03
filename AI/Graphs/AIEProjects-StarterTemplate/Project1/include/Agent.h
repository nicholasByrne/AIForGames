#pragma once
#include <list>
#include "Vector2.h"
#include "GameObject.h"

class IBehaviour;
class Decision;

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

	Agent* m_target; //other agent, used by some decisions
	Decision* m_decision; //root decision
	float m_timer; //used by some decisions

protected:
	std::list<IBehaviour*> m_behaviours;
	IBehaviour* m_behaviourTree; //root node of tree
	//Agent* m_targetAgent;
};


