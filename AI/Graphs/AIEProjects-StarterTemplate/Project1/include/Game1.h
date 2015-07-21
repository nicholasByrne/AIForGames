
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
#include "BehaviourPack.h"

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



protected:
	int *xpos;
	int *ypos;
	std::vector<GameObject*> gameObjectVector;
	Font* m_arielFont;
	SpriteBatch *m_spritebatch;
	Graph * myGraph;


	Vector2 mousePos;

	Texture* m_textureBox;
private:
};

#endif