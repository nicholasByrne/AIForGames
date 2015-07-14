#include "Node.h"
#include "SpriteBatch.h"

Node::Node()
{
	position.x = 0.0f;
	position.y = 0.0f;
	float gScore = 0.0f;
	float fScore = 0.0f;
	float hScore = 0.0f;
	Node *parent = nullptr;
	nodeEdges.reserve(10);
	iter = nodeEdges.begin();
}


Node::Node(float a_x, float a_y)
{
	position.x = a_x;
	position.y = a_y;		
	float gScore = 0.0f;
	Node *parent = nullptr;
	nodeEdges.reserve(10);
	iter = nodeEdges.begin();
}


Node::~Node()
{
	//delete[] nodeEdges;
}

//2 Way Edge
void Node::InsertEdge(Node * end, int a_cost)
{
	nodeEdges.push_back(new Edge(this, end, a_cost));
	end->nodeEdges.push_back(new Edge(end, this, a_cost));
}

//TODO? make 2way edge removal?
void Node::RemoveEdge(Node * toRemove)
{
	//for (int i = 0; i < nodeEdges.size(); i++)
	//{
	//	for (int j = 0; j < nodeEdges[i]->endNode->nodeEdges.size(); j++)
	//	{
	//		if (nodeEdges[i]->endNode->nodeEdges[j]->endNode == this)
	//		{
	//			delete nodeEdges[i]->endNode->nodeEdges[j];
	//			nodeEdges[i]->endNode->nodeEdges.erase(j);
	//		}
	//	}
	//}
	//
	//std::vector<Edge*>::iterator jiter;
	//for (iter = nodeEdges.begin(); iter != nodeEdges.end(); iter++)
	//{
	//	for (jiter = (*iter)->endNode->nodeEdges.begin(); jiter != (*iter)->endNode->nodeEdges.end(); jiter++)
	//	{
	//		if ((*jiter)->endNode == toRemove)
	//		{
	//			(*iter)->
	//		}
	//	}
	//
	//}

	for (iter = nodeEdges.begin(); iter != nodeEdges.end();)
	{
		if ((*iter)->endNode == toRemove)
		{
			nodeEdges.erase(iter);
		}
		else 
			iter++;
	}
}

void Node::DrawEdge(SpriteBatch & a_spriteBatch, Edge * edge, float thickness)
{
	if (edge != nullptr)
		a_spriteBatch.DrawLine(edge->startNode->position.x, edge->startNode->position.y, edge->endNode->position.x, edge->endNode->position.y, 2.0f);
}


void Node::DrawEdgeAll(SpriteBatch & a_spriteBatch, float thickness)
{
	for (iter = nodeEdges.begin(); iter != nodeEdges.end(); iter++)
	{
		DrawEdge(a_spriteBatch, *iter, thickness);
	}
}



//Vector2::Vector2()
//{
//	x = 0;
//	y = 0;
//}
//
//
//Vector2::Vector2(float a_x, float a_y)
//{
//	x = a_x;
//	y = a_y;
//}
//
//
//Vector2::~Vector2()
//{
//
//}
//
//
//Vector2::Vector2(Vector2 &other)
//{
//	x = other.x;
//	y = other.y;
//}
