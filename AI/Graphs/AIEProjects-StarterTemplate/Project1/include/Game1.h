
/*-----------------------------------------------------------------------------
Author:			
Description:	
-----------------------------------------------------------------------------*/
#ifndef GAME1_H
#define GAME1_H
#
#include "Application.h"
#include "Graph.h"
#include "GameObject.h"
#include "Agent.h"
#include <vector>
#include <list>
#include "BehaviourPack.h"
#include "CollisionManager.h"
#include "GameObjectPool.h"

class SpriteBatch;

class Game1 : public Application
{
public:

	// assets loaded in constructor
	Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title);

	// assets destroyed in destructor
	virtual ~Game1();

	// update / draw called each frame automaticly
	virtual void Update(float deltaTime);
	virtual void Draw();

	Node* testArray[10][10];
	std::vector<Agent*>* GetGameObjectVector();

protected:
	int *xpos;
	int *ypos;
	std::vector<GameObject*> gameObjectVector;

	//Object Pool Stuff
	std::list<GameObject*> gameObjects;
	GameObjectPool gameObjectPool;


	std::vector<Agent*> gameObjectVector;

	Font* m_arielFont;
	SpriteBatch *m_spritebatch;
	Graph * myGraph;
	bool drawShortestPath;
	std::list<Vector2> shortestPath;
	
	Vector2 mousePos;

	Texture* m_textureBox;
private:
};

#endif