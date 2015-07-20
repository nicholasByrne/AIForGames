#include "GameObject.h"


GameObject::GameObject()
{
	m_texture = nullptr;
	m_position = Vector2(0, 0);
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_friction = 1;
	m_scale = 1;
	m_mass = 1;
	//m_spriteBatch = nullptr;
}


GameObject::~GameObject()
{

}


void GameObject::AddForce(Vector2& a_force)
{
	m_acceleration += a_force / m_mass;
}