#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
	xpos = new int;
	ypos = new int;
	m_spritebatch = SpriteBatch::Factory::Create(this, SpriteBatch::GL3);
	myGraph = new Graph();
	m_arielFont = new Font("./Fonts/arial_20px.fnt");
	//myGraph->AddNode(35, 420);
	//myGraph->AddNode(500, 560);
	//myGraph->AddNode(250, 40);
	//myGraph->AddNode(100, 350);

	//myGraph->a_nodeVector[0]->InsertEdge(myGraph->a_nodeVector[1], 10);
	//myGraph->a_nodeVector[1]->InsertEdge(myGraph->a_nodeVector[2], 10);

	//myGraph->PrintBFS(*myGraph->a_nodeVector.begin());

	m_textureBox = new Texture("./Images/box0_256.png");
	drawShortestPath = false;
	gameObjectVector.push_back(new Agent(mousePos, m_textureBox, m_spritebatch));

}

Game1::~Game1()
{
	delete xpos;
	delete ypos;
	SpriteBatch::Factory::Destroy(m_spritebatch);
	delete myGraph;

	delete m_textureBox;
	for (int i = 0; i < gameObjectVector.size(); ++i)
	{
		delete gameObjectVector[i];
	}
	gameObjectVector.clear();
	
}


//if (GetInput()->IsKeyDown(GLFW_KEY_D))
//if (GetInput()->IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)) //1=L, 2=R
void Game1::Update(float deltaTime)
{
	GetInput()->GetMouseXY(xpos, ypos);
	float mousePosx = (float)*xpos;
	float mousePosy = (float)*ypos;


	mousePos.x = mousePosx;
	mousePos.y = mousePosy;

	//Behaviours
	//Object at mouse
	gameObjectVector[0]->m_position.x = mousePos.x;
	gameObjectVector[0]->m_position.y = mousePos.y;
	
	if (GetInput()->WasKeyPressed(GLFW_KEY_Q))
	{
		gameObjectVector.push_back(new Agent(mousePos, m_textureBox, m_spritebatch));
	}

	//if (GetInput()->WasKeyPressed(GLFW_KEY_S))
	//{
	//	//Agent* temp = new Agent(Vector2(mousePosx, mousePosy), m_textureBox, m_spritebatch);
	//	//temp->AddBehaviour(new Arrive(&mousePos, 500));
	//	//gameObjectVector.push_back(temp);
	//}

	//Seek
	if (GetInput()->WasKeyPressed(GLFW_KEY_1) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Seek(*gameObjectVector[0]));
		}
	}
	//Flee
	if (GetInput()->WasKeyPressed(GLFW_KEY_2) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Flee(*gameObjectVector[0]));
		}
	}
	//Wander
	//Pursue
	if (GetInput()->WasKeyPressed(GLFW_KEY_4) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Pursue(*gameObjectVector[0]));
		}
	}
	//Evade TODO
	if (GetInput()->WasKeyPressed(GLFW_KEY_5) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Evade(*gameObjectVector[0]));
		}
	}
	//Arrive
	if (GetInput()->WasKeyPressed(GLFW_KEY_6) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Arrive(*gameObjectVector[0], 200.0f));
		}
	}
	//Avoid TODO //used ontop of other behaviours
	if (GetInput()->WasKeyPressed(GLFW_KEY_7) && gameObjectVector.size() > 1)
	{
		for (int i = 1; i < gameObjectVector.size(); ++i)
		{
			if (gameObjectVector[i]->m_behaviours.empty() != true)
			gameObjectVector[i]->m_behaviours.pop_front();
			gameObjectVector[i]->AddBehaviour(new Avoid(gameObjectVector, 200.0f, 200.0f));
		}
	}

	//GRAPH
	if (GetInput()->WasMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		//if node is already selected, and node is clicked
		if ((myGraph->selectedNode != nullptr) && (myGraph->GraphNodeClicked(mousePos) != nullptr))
		{
			//create edge between, w/ cost //  Cost = Vector2::Distance(myGraph->selectedNode->position, myGraph->GraphNodeClicked(mousePosx, mousePosy))
			myGraph->selectedNode->InsertEdge(myGraph->GraphNodeClicked(mousePos), Vector2::Distance(myGraph->selectedNode->position, Vector2(myGraph->GraphNodeClicked(mousePosx, mousePosy)->position)));
			//myGraph->selectedNode->InsertEdge(myGraph->GraphNodeClicked(mousePosx, mousePosy), 0);
			myGraph->selectedNode = nullptr;
		}
		//if node is already selected, and an empty space is clicked
		else if ((myGraph->selectedNode != nullptr) && (myGraph->GraphNodeClicked(mousePos) == nullptr))
		{
			//unselect node
			myGraph->selectedNode = nullptr;
		}
		//if a node is not selected, and a node is clicked
		else if (myGraph->GraphNodeClicked(mousePos) != nullptr)
		{
			//select node
			myGraph->selectedNode = myGraph->GraphNodeClicked(mousePos);
		}
		else
			//if a node is not selected, and an empty space is clicked
			myGraph->AddNode(mousePos);
	}

	if (GetInput()->WasMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		Node* removeNode = myGraph->GraphNodeClicked(mousePos);
		if (removeNode != nullptr)
		{
			myGraph->RemoveNode(removeNode);
			myGraph->selectedNode = nullptr;
		}
	}

	//Print Node position, and connected nodes position
	if (GetInput()->WasKeyPressed(GLFW_KEY_P))
	{
		system("cls");
		for (int i = 0; i < myGraph->a_nodeVector.size(); i++)
		{
			std::cout << "Node " << i << ": ";
			for (int j = 0; j < myGraph->a_nodeVector[i]->nodeEdges.size(); j++)
			{
				std::cout << "(" << myGraph->a_nodeVector[i]->nodeEdges[j]->endNode->position.x << "," << myGraph->a_nodeVector[i]->nodeEdges[j]->endNode->position.y << ") ";
			}
			std::cout << std::endl;
		}
	}

	//Print FindPathDijkstras
	if (GetInput()->WasKeyPressed(GLFW_KEY_D) && drawShortestPath == false)
	{
		drawShortestPath = true;
		std::list<Node*> endNodes;
		endNodes.push_back(myGraph->a_nodeVector.back());
		shortestPath = myGraph->FindPathDijkstras(myGraph->a_nodeVector[0], endNodes);//(myGraph->a_nodeVector.begin(), endNodes);
	}
	else if (GetInput()->WasKeyPressed(GLFW_KEY_D) && myGraph->a_nodeVector.empty() != true)
	{
		drawShortestPath = false;
		shortestPath.clear();
	}



	for (int i = 0; i < gameObjectVector.size(); i++)
	{
		gameObjectVector[i]->Update(deltaTime);
	}
	std::cout << gameObjectVector.size() << std::endl;
}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	// TODO: draw stuff.

	myGraph->DrawCircleAll(m_spritebatch, 10.0f);
	myGraph->DrawEdgeAll(m_spritebatch, 10.0f);
	for (int i = 0; i < gameObjectVector.size(); ++i)
	{
		gameObjectVector[i]->Draw();
	}
	//draw shortest path
	if (drawShortestPath == true)
	{
		int i = 0;
		for (std::list<Vector2>::iterator iter = shortestPath.begin(); iter != shortestPath.end(); ++iter)
		{
			std::string jimmy = std::to_string(i);
			const char * c = jimmy.c_str();
			//char* charr;
			//charr = new char[jimmy.size() + 1];
			m_spritebatch->DrawSprite(m_textureBox, iter->x, iter->y, 50.0f, 50.0f);
			m_spritebatch->DrawString(m_arielFont, c, iter->x, iter->y + 50);
			i++;
		}
	}

	
	//draw start node
	if (myGraph->a_nodeVector.size() > 1)
	{
		m_spritebatch->SetRenderColor(255, 0, 0, 255);
		m_spritebatch->DrawSprite(m_textureBox, myGraph->a_nodeVector[0]->position.x, myGraph->a_nodeVector[0]->position.y, 50.0f, 50.0f);

		m_spritebatch->SetRenderColor(0, 0, 255, 255);
		m_spritebatch->DrawSprite(m_textureBox, myGraph->a_nodeVector.back()->position.x, myGraph->a_nodeVector.back()->position.y, 50.0f, 50.0f);
	}

	m_spritebatch->SetRenderColor(255, 255, 255, 255);
	m_spritebatch->End();

}