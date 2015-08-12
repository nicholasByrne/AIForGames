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
	void SetPath(std::list<Vector2> path);

//protected:
	Agent* m_target; //other agent, used by some decisions
	
	float m_timer; //used by some decisions

	//std::list<IBehaviour*> m_behaviours;
	IBehaviour* m_behaviourTree; //root node of tree
	std::list<Vector2> m_path;


	//Decision* m_decision; //root decision
	//Agent* m_targetAgent;
};


