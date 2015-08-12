#pragma once
#include "Vector2.h"
#include <string>

class SpriteBatch;
class Texture;

class GameObject
{
public:
	GameObject();
	GameObject(Vector2& startingPos, Texture* texture, SpriteBatch* spriteBatch);
	virtual ~GameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw();

	//static SpriteBatch* m_spriteBatch;
	Texture* m_texture;
	SpriteBatch* m_spriteBatch;
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Vector2 m_force;
	Vector2 m_scale;
	float m_friction;
	float m_mass;
	float m_maxVelocity;
	std::string tag;

	void AddForce(Vector2& a_force);

	static bool CheckCollision(GameObject* object1, GameObject* object2);
	static bool CheckCollision(Vector2& point, GameObject* object2);

private:

};

