#pragma once
#include <list>
#include "Vector2.h"
#include "GameObject.h"
#include "CollisionManager.h"

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

	void SetPath(std::list<Vector2> path);

	Vector2 m_force;

	Agent* m_target; //other agent, used by some decisions
	Decision* m_decision; //root decision
	float m_timer; //used by some decisions

//protected:
	std::list<IBehaviour*> m_behaviours;
	IBehaviour* m_behaviourTree; //root node of tree
	//Agent* m_targetAgent;

	std::list<Vector2> m_path;
};


