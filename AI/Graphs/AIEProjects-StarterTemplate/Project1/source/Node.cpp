#include "Node.h"
#include "SpriteBatch.h"
#include "Font.h"

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


void Node::DrawCircle(SpriteBatch* a_spriteBatch, float a_radius, Font* a_font)
{
	
	Vector2 oldPos = Vector2(position.x + (cos(0.0f) * a_radius), position.y + (sin(0.0f) * a_radius));

	for (float i = 0; i < 2 * 3.1457f; i += 3.1457f / 10.0f)
	{
		Vector2 newPos;

		newPos.x = position.x + (cos(i) * a_radius);
		newPos.y = position.y + (sin(i) * a_radius);

		a_spriteBatch->DrawLine(oldPos.x, oldPos.y, newPos.x, newPos.y, 2.0f);

		oldPos = newPos;
	}
}


void Node::DrawEdge(SpriteBatch* a_spriteBatch, Edge * edge, float thickness)
{
	if (edge != nullptr)
		a_spriteBatch->DrawLine(edge->startNode->position.x, edge->startNode->position.y, edge->endNode->position.x, edge->endNode->position.y, 2.0f);
}


void Node::DrawEdgeAll(SpriteBatch* a_spriteBatch, float thickness)
{
	for (iter = nodeEdges.begin(); iter != nodeEdges.end(); iter++)
	{
		DrawEdge(a_spriteBatch, *iter, thickness);
	}
}




