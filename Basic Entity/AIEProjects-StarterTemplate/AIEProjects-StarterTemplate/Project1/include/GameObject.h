#pragma once
#include "Vector2.h"
class Texture;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_Acceleration;
	float m_friction;

	Texture* m_texture;
	float m_scale;

	virtual void Update(float deltaTime);
	void Draw();
};

