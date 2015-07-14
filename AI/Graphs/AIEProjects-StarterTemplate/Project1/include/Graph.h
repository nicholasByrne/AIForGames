#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include "SpriteBatch.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>

class Graph
{
public:
	Graph();
	~Graph();

	std::vector<Node*> a_nodeVector;
	std::vector<Node*>::iterator iter;
	Node* selectedNode;

	void RemoveNode(Node * toRemove);
	void AddNode(float x, float y);

	//float CompareGScore(Node* first, Node* second);
	//float CompareFScore(Node* first, Node* second);

	void BFS(Node* startNode);
	void DFS(Node* startNode);
	void BFS_DFS(Node* startNode);
	void FindPathDijkstras();
	void FindPathDijkstras(Node *startNode, std::list<Node*> &potentialEndNodes);
	void FindAStar(Node* startNode, Node* endNode);

	void PrintBFS(Node* startNode);
	void PrintDFS(Node* startNode);

	//Printing
	void DrawCircle(SpriteBatch& a_spriteBatch, Vector2 pos, float radius);
	void DrawCircleAll(SpriteBatch& a_spriteBatch, float radius);
	void DrawEdgeAll(SpriteBatch & a_spriteBatch, float thickness);

	//returns nullptr if not clicked within 50 pixel of node
	Node* GraphNodeClicked(float a_x, float a_y);



	struct CompareGScorePlz
	{
		bool operator()(Node * lhs, Node * rhs)
		{
			return lhs->gScore < rhs->gScore;
		}
	};

	struct CompareFScorePlz
	{
		bool operator()(Node * lhs, Node * rhs)
		{
			return lhs->fScore < rhs->fScore;
		}
	};

private:

};

#endif