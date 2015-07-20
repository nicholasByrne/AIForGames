#pragma once
#include "Vector2.h"
#include "SpriteBatch.h"


class GameObject
{
public:
	GameObject(); // : m_texture(nullptr), m_position(Vector2()){}
	virtual ~GameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw()
	{
		//m_spriteBatch->DrawSprite(m_texture, m_position.x, m_position.y);
	}

	//static SpriteBatch* m_spriteBatch;
	Texture* m_texture;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Vector2 m_force;
	float m_friction;
	float m_scale;
	float m_mass;
	float m_maxVelocity;

	void AddForce(Vector2& a_force);

private:

};

