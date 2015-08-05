#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
//#include "SpriteBatch.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>

class SpriteBatch;

class Graph
{
public:
	Graph();
	~Graph();

	std::vector<Node*> a_nodeVector;
	std::vector<Node*>::iterator iter;
	Node* selectedNode;

	Node* m_startNode;
	Node* m_endNode;

	void RemoveNode(Node * toRemove);
	void AddNode(float x, float y);
	void AddNode(Vector2& vectorA);

	//float CompareGScore(Node* first, Node* second);
	//float CompareFScore(Node* first, Node* second);

	void BFS(Node* startNode);
	void DFS(Node* startNode);
	void BFS_DFS(Node* startNode);
	void FindPathDijkstras();
	std::list<Vector2> FindPathDijkstras(Node *startNode, std::list<Node*> &potentialEndNodes);
	std::list<Vector2> FindAStar(Node* startNode, Node* endNode);

	void PrintBFS(Node* startNode);
	void PrintDFS(Node* startNode);

	//Printing
	void DrawCircle(SpriteBatch* a_spriteBatch, Vector2 pos, float radius);
	void DrawCircle(SpriteBatch* a_spriteBatch, Vector2 pos, float radius, Font* a_font); //With number under it
	void DrawCircleAll(SpriteBatch* a_spriteBatch, float radius);
	void DrawCircleAll(SpriteBatch* a_spriteBatch, float radius, Font* a_font); //With numbers under them
	void DrawEdgeAll(SpriteBatch* a_spriteBatch, float thickness);

	//returns nullptr if not clicked within 50 pixel of node
	Node* GraphNodeClicked(float a_x, float a_y);
	Node* GraphNodeClicked(Vector2& vectorA);


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