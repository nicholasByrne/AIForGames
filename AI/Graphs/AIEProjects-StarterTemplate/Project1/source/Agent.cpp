#include "Agent.h"
#include "IBehaviour.h"
#include "BehaviourPack.h"

Agent::Agent()
{
	tag = "Agent";
}


Agent::Agent(Vector2& startingPos, Texture* texture, SpriteBatch* spriteBatch)
{
	tag = "Agent";
	m_texture = texture;
	m_spriteBatch = spriteBatch;
	m_position = startingPos;
	m_maxVelocity = 400.0f;
	/*m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_friction = 1;
	m_mass = 1;*/

	m_scale = Vector2(0.25f, 0.25f);
}


Agent::~Agent()
{
	
	for (std::list<IBehaviour*>::iterator iter = m_behaviours.begin(); iter != m_behaviours.end(); ++iter)
	{
		delete (*iter);
	}
	m_behaviours.clear();
}


void Agent::Update(float deltaTime)
{
	//iterator
	std::list<IBehaviour*>::iterator iter;
	//Sensing

	//Thinking
		//Add or remove behaviours from m_behaviours list





	
	//Acting
	for (iter = m_behaviours.begin(); iter != m_behaviours.end(); ++iter)
	{
		(*iter)->Update(this, deltaTime);
	}

	//m_behaviours.clear();

	m_velocity += m_acceleration * deltaTime;

	if (m_velocity.Magnitude() > m_maxVelocity)
		m_velocity = m_velocity.Normalise()*m_maxVelocity;


	m_position += m_velocity * deltaTime;

	//clamp it!!! THIS DOESN'T CLAMP IT!
	//m_velocity *= m_friction;


	m_acceleration = Vector2(0.0f, 0.0f);
}


//void Agent::Draw()
//{
//
//}


void Agent::AddBehaviour(IBehaviour* a_behaviour)
{
	m_behaviours.push_back(a_behaviour);
}