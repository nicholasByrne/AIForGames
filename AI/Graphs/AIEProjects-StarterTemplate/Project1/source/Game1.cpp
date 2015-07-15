#include "Game1.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>

Game1::Game1(unsigned int windowWidth, unsigned int windowHeight, bool fullscreen, const char *title) : Application(windowWidth, windowHeight, fullscreen, title)
{
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
}

Game1::~Game1()
{
	SpriteBatch::Factory::Destroy(m_spritebatch);
}


//if (GetInput()->IsKeyDown(GLFW_KEY_D)
//if (GetInput()->IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)) //1=L, 2=R
void Game1::Update(float deltaTime)
{
	int *ypos = new int;
	int *xpos = new int;
	GetInput()->GetMouseXY(xpos, ypos);
	float mousePosx = (float)*xpos;
	float mousePosy = (float)*ypos;

	if (GetInput()->WasMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		//if node is already selected, and node is clicked
		if ((myGraph->selectedNode != nullptr) && (myGraph->GraphNodeClicked(mousePosx, mousePosy) != nullptr))
		{
			//create edge between, w/ cost //  Cost = Vector2::Distance(myGraph->selectedNode->position, myGraph->GraphNodeClicked(mousePosx, mousePosy))
			myGraph->selectedNode->InsertEdge(myGraph->GraphNodeClicked(mousePosx, mousePosy), Vector2::Distance(myGraph->selectedNode->position, Vector2(myGraph->GraphNodeClicked(mousePosx, mousePosy)->position)));
			//myGraph->selectedNode->InsertEdge(myGraph->GraphNodeClicked(mousePosx, mousePosy), 0);
			myGraph->selectedNode = nullptr;
		}
		//if node is already selected, and an empty space is clicked
		else if((myGraph->selectedNode != nullptr) && (myGraph->GraphNodeClicked(mousePosx, mousePosy) == nullptr))
		{
			//unselect node
			myGraph->selectedNode = nullptr;
		}
		//if a node is not selected, and a node is clicked
		else if (myGraph->GraphNodeClicked(mousePosx, mousePosy) != nullptr)
		{
			//select node
			myGraph->selectedNode = myGraph->GraphNodeClicked(mousePosx, mousePosy);
		}
		else
			//if a node is not selected, and an empty space is clicked
			myGraph->AddNode(mousePosx, mousePosy);
	}

	if (GetInput()->WasMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		Node* removeNode = myGraph->GraphNodeClicked(mousePosx, mousePosy);
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



}

void Game1::Draw()
{
	// clear the back buffer
	ClearScreen();

	m_spritebatch->Begin();

	// TODO: draw stuff.

	myGraph->DrawCircleAll(m_spritebatch, 10.0f);
	myGraph->DrawEdgeAll(m_spritebatch, 10.0f);


	m_spritebatch->End();

}