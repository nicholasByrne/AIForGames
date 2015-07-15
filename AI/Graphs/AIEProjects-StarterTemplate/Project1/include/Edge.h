#ifndef EDGE_H 
#define EDGE_H
#include "Vector2.h"

class Node;
class SpriteBatch;

class Edge
{
public:
	Edge();
	Edge(Node * start, Node * end, int a_cost);
	~Edge();

	Node * startNode;
	Node * endNode;
	int cost;

	
};

#endif