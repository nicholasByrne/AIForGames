#include "Player.h"
#include "Input.h"
#include "glfw3.h"

Input* Player::input = nullptr;

Player::Player()
{

}


Player::~Player()
{

}


void Player::Update(float a_deltaTime)
{
	float movementSpeed = 10.0f * a_deltaTime;

	if (input->IsKeyDown(GLFW_KEY_W))
	{
		m_position += Vector2::Vector2(0.f, -movementSpeed);
	}
	if (input->IsKeyDown(GLFW_KEY_S))
	{
		m_position += Vector2::Vector2(0.f, movementSpeed);
	}
	if (input->IsKeyDown(GLFW_KEY_A))
	{
		m_position += Vector2::Vector2(-movementSpeed, 0.f);
	}
	if (input->IsKeyDown(GLFW_KEY_D))
	{
		m_position += Vector2::Vector2(movementSpeed, 0.f);
	}
}