#include "GameEngine.hpp"

GameEngine::GameEngine()
	: m_isRunning(true)
{ 
}

void GameEngine::Init()
{
	m_window.create(sf::VideoMode(m_resolution), "Sonic C++");

	Update();
}

void GameEngine::Draw()
{
	m_window.clear(sf::Color(10,10,10));
	
	//A shape for testing
	sf::CircleShape testShape(50, 3);
	testShape.setPosition({(float)m_resolution.x/2, (float)m_resolution.y/2});
	testShape.setFillColor(sf::Color::White);
	testShape.setRotation(sf::degrees(m_testShapeAngle));
	
	m_window.draw(testShape);

	m_window.display();
}

void GameEngine::Update()
{
	while(m_isRunning)
	{

		m_testShapeAngle += 0.1;

		Draw();

		//Checks to see if the window's x has been pressed.
		while(const std::optional event = m_window.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			{
				m_window.close();
				m_isRunning = false;
			}
		}
	}

}
