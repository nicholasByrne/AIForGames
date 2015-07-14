#include "GameObject.h"


GameObject::GameObject()
{
	m_position = Vector2(0, 0);
	m_velocity = Vector2(0, 0);
	m_Acceleration = Vector2(0, 0);
	m_friction = 0;
	m_scale = 1;
}


GameObject::~GameObject()
{

}


void GameObject::Update(float deltaTime)
{
	
}


void GameObject::Draw()
{

}

