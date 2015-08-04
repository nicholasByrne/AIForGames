#ifndef NODE_H 
#define NODE_H
#include <vector>
#include "Edge.h"

class Font;

class Node
{
public:
	Node();
	Node(float a_x, float a_y);
	~Node();

	Vector2 position;
	float gScore;
	float hScore;
	float fScore;
	Node *parentNode;
	bool traversed = false;

	std::vector<Edge*> nodeEdges;
	std::vector<Edge*>::iterator iter;

	void InsertEdge(Node * end);
	void InsertEdge(Node * end, int a_cost);
	void RemoveEdge(Node * edgeEndNode);

	void DrawCircle(SpriteBatch* a_spriteBatch, float a_radius, Font* a_font);
	void DrawEdge(SpriteBatch* a_spriteBatch, Edge * edge, float thickness);
	void DrawEdgeAll(SpriteBatch* a_spriteBatch, float thickness);


private:

};



#endif