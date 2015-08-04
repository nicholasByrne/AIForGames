#include "GameObject.h"
#include "SpriteBatch.h"
#include "Texture.h"

GameObject::GameObject()
{
	m_texture = nullptr;
	m_position = Vector2(0, 0);
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_scale = Vector2(1, 1);
	m_friction = 1;
	m_mass = 1;
	//m_spriteBatch = nullptr;
}


GameObject::GameObject(Vector2& startingPos, Texture* texture, SpriteBatch* spriteBatch)
{
	m_texture = texture;
	m_spriteBatch = spriteBatch;
	m_position = startingPos;
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0.0);
	m_scale = Vector2(1, 1);
	m_friction = 1;
	m_mass = 1;
}


GameObject::~GameObject()
{
	
}


void GameObject::Draw()
{
	m_spriteBatch->DrawSprite(m_texture, m_position.x, m_position.y, m_scale.x * m_texture->GetWidth(), m_scale.y * m_texture->GetHeight());

	//m_spriteBatch->DrawSprite(m_texture, m_position.x, m_position.y, m_scale.x * 200, m_scale.y * 200);
}

void GameObject::AddForce(Vector2& a_force)
{
	m_acceleration += a_force / m_mass;
}


bool GameObject::CheckCollision(GameObject* object1, GameObject* object2)
{
	Vector2 temp(object1->m_position - object2->m_position);
	float radii = object1->m_scale.x * object1->m_texture->GetWidth() / 2.0f + object2->m_scale.y * object2->m_texture->GetWidth() / 2.0f;

	//if a^2 + b^2 > c^2
	if (temp.MagnitudeSqrd() < (radii * radii))
		return true;
	else
		return false;
}


bool GameObject::CheckCollision(Vector2& point, GameObject* object2)
{
	Vector2 temp(point - object2->m_position);
	float radii = object2->m_scale.y * object2->m_texture->GetWidth() / 2.0f;

	//if a^2 + b^2 > c^2
	if (temp.MagnitudeSqrd() < (radii * radii))
		return true;
	else
		return false;
}