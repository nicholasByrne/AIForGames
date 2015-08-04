#include "Graph.h"
#include <math.h>
#include <iostream>
#include <limits>
#include "SpriteBatch.h"

Graph::Graph()
{
	a_nodeVector.reserve(10);
	iter = a_nodeVector.begin();

	selectedNode = nullptr;
	m_startNode = nullptr;
	m_endNode = nullptr;
	
}

Graph::~Graph()
{
	for (int i = 0; i < a_nodeVector.size(); ++i)
	{
		delete a_nodeVector[i];
	}
	a_nodeVector.clear();

	delete selectedNode;
	delete m_startNode;
	delete m_endNode;
}


void Graph::RemoveNode(Node * toRemove)
{
	//remove edges from other nodes to node
	for (iter = a_nodeVector.begin(); iter != a_nodeVector.end(); iter++)
	{
		(*iter)->RemoveEdge(toRemove);		
	}

	for (iter = a_nodeVector.begin(); iter != a_nodeVector.end();)
	{
		if ((*iter) == toRemove)
		{
			//delete (*iter);
			iter = a_nodeVector.erase(iter);
			break;
		}
		else
			iter++;
	}

	//for (iter = a_nodeVector.begin(); iter != a_nodeVector.end(); iter++)
	//{
	//	if ((*iter) == toRemove)
	//	{
	//		//if 2way edge, remove edge to this, first
	//		toRemove->RemoveEdge((*iter));
	//		//then remove edge from this
	//		(*iter)->RemoveEdge(toRemove);
	//	}
	//	//(*iter)->RemoveEdge(toRemove);	
	//}
	//
	////remove node
	//for (iter = a_nodeVector.begin(); iter != a_nodeVector.end(); iter++)
	//{
	//	if ((*iter) == toRemove)
	//	{
	//		delete (*iter);
	//		a_nodeVector.erase(iter);
	//		break;
	//	}
	//}
}


void Graph::AddNode(float x, float y)
{
	a_nodeVector.push_back(new Node(x, y));
}

void Graph::AddNode(Vector2& vectorA)
{
	AddNode(vectorA.x, vectorA.y);
}



//float Graph::CompareFScore(Node* first, Node* second)
//{
//	return first->fScore > second->fScore;
//}


void Graph::BFS(Node* startNode)
{
	std::queue<Node*> openList;
	std::list<Node*> closedList;
	std::list<Node*>::iterator closedListIter;

	Node* currentNode;
	openList.push(startNode);

	while (openList.empty() != true)
	{
		currentNode = openList.front();

		openList.pop();
		closedList.push_back(currentNode);

		//for all connections in currentNode
		for (currentNode->iter = currentNode->nodeEdges.begin(); currentNode->iter != currentNode->nodeEdges.end(); currentNode->iter++)
		{
			bool nodeInClosedList = false;
			//check closedList
			for (closedListIter = closedList.begin(); closedListIter != closedList.end(); closedListIter++)
			{
				//if in closedList
				if ((*closedListIter) == (*currentNode->iter)->endNode)
				{
					nodeInClosedList = true;
					break;
				}
			}
			//if not in closed list
			if (nodeInClosedList == false)
			{
				closedList.push_back((*currentNode->iter)->endNode);
			}
		}
	}
}


void Graph::DFS(Node* startNode)
{
	std::stack<Node*> openStack;
	std::list<Node*> closedList;
	std::list<Node*>::iterator closedListIter;

	Node* currentNode;
	openStack.push(startNode);

	while (openStack.empty() != true)
	{
		currentNode = openStack.top();

		openStack.pop();
		closedList.push_back(currentNode);

		//for all connections in currentNode
		for (currentNode->iter = currentNode->nodeEdges.begin(); currentNode->iter != currentNode->nodeEdges.end(); currentNode->iter++)
		{
			bool nodeInClosedList = false;
			//check closedList
			for (closedListIter = closedList.begin(); closedListIter != closedList.end(); closedListIter++)
			{
				//if in closedList
				if ((*closedListIter) == (*currentNode->iter)->endNode)
				{
					nodeInClosedList = true;
					break;
				}
			}
			//if not in closed list
			if (nodeInClosedList == false)
			{
				closedList.push_back((*currentNode->iter)->endNode);
			}
		}
	}
}


void Graph::BFS_DFS(Node* startNode)
{

}



std::list<Vector2> Graph::FindPathDijkstras(Node *startNode, std::list<Node*> &potentialEndNodes)
{
	for (int i = 0; i < a_nodeVector.size(); i++)
	{
		a_nodeVector[i]->parentNode = nullptr;
		a_nodeVector[i]->gScore = std::numeric_limits<float>::max();
		a_nodeVector[i]->traversed = false;
	}

	std::list<Node*> openList;
	//std::list<Node*> closeList;
	Node* currentNode;
	Node* endNode = nullptr;
	openList.push_front(startNode);
	openList.front()->gScore = 0;

	while (openList.empty() != true)
	{
		//sort list by gScore
		openList.sort(CompareGScorePlz());

		currentNode = openList.front();
		currentNode->traversed = true;

		//if currentNode == potentialEndNode, break loop
		std::list<Node*>::iterator jiter; 
		bool breakloop = false;
		for (std::list<Node*>::iterator jiter = potentialEndNodes.begin(); jiter != potentialEndNodes.end(); jiter++)
		{
			if (currentNode == (*jiter))
			{
				endNode = currentNode;
				breakloop == true;
				break;
			}
		}
		if (breakloop == true)
			break;

		//erase currentnode from openList
		jiter = openList.begin();
		openList.erase(jiter); //erase needs an iterator
		//closeList.push_back(currentNode);

		//Add connections to openList if not traversed
		for (int i = 0; i < currentNode->nodeEdges.size(); i++)
		{	//if new node is found
			if (currentNode->nodeEdges[i]->endNode->traversed == false)
			{
				float newG = currentNode->gScore + currentNode->nodeEdges[i]->cost;
				if (newG < currentNode->nodeEdges[i]->endNode->gScore)
				{
					currentNode->nodeEdges[i]->endNode->gScore = currentNode->gScore + currentNode->nodeEdges[i]->cost;
					currentNode->nodeEdges[i]->endNode->parentNode = currentNode;
						
					//if node already on the openlist (don't re-add it) <- TODO ?
					openList.push_back(currentNode->nodeEdges[i]->endNode);
				}
			}
		}
	}

	//calculate path
	std::list<Vector2> path;
	currentNode = endNode;
	while (currentNode != nullptr)
	{
		path.push_front(currentNode->position);
		currentNode = currentNode->parentNode;
	}
	return path;
}


void Graph::FindAStar(Node* startNode, Node* endNode)
{
	for (int i = 0; i < a_nodeVector.size(); i++)
	{
		a_nodeVector[i]->parentNode = nullptr;
		a_nodeVector[i]->gScore = std::numeric_limits<float>::max();
		a_nodeVector[i]->hScore = 0;
		a_nodeVector[i]->fScore = 0;
		a_nodeVector[i]->traversed = false;
	}

	std::list<Node*> openList;
	std::list<Node*> closeList;

	Node* currentNode;
	openList.push_front(startNode);

	while (openList.empty() != true)
	{
		openList.sort(CompareFScorePlz());

		currentNode = openList.front();

		if (currentNode == endNode)
		{
			break;
		}

		openList.pop_front();
		currentNode->traversed = true;

		//for all edges
		for (int i = 0; i < currentNode->nodeEdges.size(); i++)
		{
			float gScore = currentNode->gScore + currentNode->nodeEdges[i]->cost;
			//if new shortest path
			if ((currentNode->nodeEdges[i]->endNode->parentNode == nullptr) || (currentNode->nodeEdges[i]->endNode->gScore < gScore))
			{
				currentNode->nodeEdges[i]->endNode->traversed = true;
				currentNode->nodeEdges[i]->endNode->gScore = gScore;
				currentNode->nodeEdges[i]->endNode->hScore = Vector2::Distance(currentNode->nodeEdges[i]->endNode->position, endNode->position);
				currentNode->nodeEdges[i]->endNode->fScore = currentNode->nodeEdges[i]->endNode->gScore + currentNode->nodeEdges[i]->endNode->hScore;
				currentNode->nodeEdges[i]->endNode->parentNode = currentNode;
			}
			if (currentNode->nodeEdges[i]->endNode->traversed == false)
				currentNode->nodeEdges[i]->endNode->traversed = true;
		}
	}

	//calculate path
	std::list<Vector2> path;
	currentNode = endNode;
	while (currentNode != nullptr)
	{
		path.push_front(currentNode->position);
		currentNode = currentNode->parentNode;
	}

}


void Graph::PrintBFS(Node* startNode)
{
	std::queue<Node*> openList;
	std::list<Node*> closedList;
	std::list<Node*>::iterator closedListIter;

	Node* currentNode;
	openList.push(startNode);

	while (openList.empty() != true)
	{
		currentNode = openList.front();
		std::cout << "Node(" << currentNode->position.x << "," << currentNode->position.y << ")" << std::endl;
		openList.pop();
		closedList.push_back(currentNode);

		//for all connections in currentNode
		for (currentNode->iter = currentNode->nodeEdges.begin(); currentNode->iter != currentNode->nodeEdges.end(); currentNode->iter++)
		{
			bool nodeInClosedList = false;
			//check closedList
			for (closedListIter = closedList.begin(); closedListIter != closedList.end(); closedListIter++)
			{
				//if in closedList
				if ((*closedListIter) == (*currentNode->iter)->endNode)
				{
					nodeInClosedList = true;
					break;
				}
			}
			//if not in closed list
			if (nodeInClosedList == false)
			{
				closedList.push_back((*currentNode->iter)->endNode);
			}
		}
	}
}


void Graph::PrintDFS(Node* startNode)
{
	std::stack<Node*> openStack;
	std::list<Node*> closedList;
	std::list<Node*>::iterator closedListIter;

	Node* currentNode;
	openStack.push(startNode);

	while (openStack.empty() != true)
	{
		currentNode = openStack.top();

		std::cout << "Node(" << currentNode->position.x << "," << currentNode->position.y << ")" << std::endl;

		openStack.pop();
		closedList.push_back(currentNode);

		//for all connections in currentNode
		for (currentNode->iter = currentNode->nodeEdges.begin(); currentNode->iter != currentNode->nodeEdges.end(); currentNode->iter++)
		{
			bool nodeInClosedList = false;
			//check closedList
			for (closedListIter = closedList.begin(); closedListIter != closedList.end(); closedListIter++)
			{
				//if in closedList
				if ((*closedListIter) == (*currentNode->iter)->endNode)
				{
					nodeInClosedList = true;
					break;
				}
			}
			//if not in closed list
			if (nodeInClosedList == false)
			{
				closedList.push_back((*currentNode->iter)->endNode);
			}
		}
	}
}


void Graph::DrawCircle(SpriteBatch* a_spriteBatch, Vector2 pos, float radius)
{
	Vector2 oldPos = Vector2(pos.x + (cos(0.0f) * radius), pos.y + (sin(0.0f) * radius));

	for (float i = 0; i < 2 * 3.1457f; i += 3.1457f / 10.0f)
	{
		Vector2 newPos;

		newPos.x = pos.x + (cos(i) * radius);
		newPos.y = pos.y + (sin(i) * radius);

		a_spriteBatch->DrawLine(oldPos.x, oldPos.y, newPos.x, newPos.y, 2.0f);

		oldPos = newPos;
	}
}


void Graph::DrawCircle(SpriteBatch* a_spriteBatch, Vector2 pos, float radius, Font* a_font)
{
	Vector2 oldPos = Vector2(pos.x + (cos(0.0f) * radius), pos.y + (sin(0.0f) * radius));

	for (float i = 0; i < 2 * 3.1457f; i += 3.1457f / 10.0f)
	{
		Vector2 newPos;

		newPos.x = pos.x + (cos(i) * radius);
		newPos.y = pos.y + (sin(i) * radius);

		a_spriteBatch->DrawLine(oldPos.x, oldPos.y, newPos.x, newPos.y, 2.0f);

		oldPos = newPos;
	}
}


void Graph::DrawCircleAll(SpriteBatch* a_spriteBatch, float radius)
{
	for (int i = 0; i < a_nodeVector.size(); i++)
	{
		DrawCircle(a_spriteBatch, a_nodeVector[i]->position, radius);
	}
}


void Graph::DrawCircleAll(SpriteBatch* a_spriteBatch, float radius, Font* a_font)
{
	for (int i = 0; i < a_nodeVector.size(); i++)
	{
		DrawCircle(a_spriteBatch, a_nodeVector[i]->position, radius, a_font);
	}
}


void Graph::DrawEdgeAll(SpriteBatch* a_spriteBatch, float thickness)
{
	for (iter = a_nodeVector.begin(); iter != a_nodeVector.end(); iter++)
	{
		(*iter)->DrawEdgeAll(a_spriteBatch, thickness);
	}
}


Node* Graph::GraphNodeClicked(float a_x, float a_y)
{
	Vector2 temp;
	float radii;
	for (int i = 0; i < a_nodeVector.size(); i++)
	{
		temp.x = a_x;
		temp.y = a_y;
		temp -= a_nodeVector[i]->position;
		radii = 50;

		if (temp.MagnitudeSqrd() < (radii * radii))
			return a_nodeVector[i];
	}
	return nullptr;
}


Node* Graph::GraphNodeClicked(Vector2& vectorA)
{
	return GraphNodeClicked(vectorA.x, vectorA.y);
}
