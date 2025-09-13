#pragma once

#include <SFML/Graphics.hpp>

class GameEngine
{
	sf::Vector2u		m_resolution 		= {1080, 720};
	sf::RenderWindow	m_window;
	bool			m_isRunning 		= false;
	float			m_testShapeAngle	= 0.0f;

public:

	GameEngine();
	void Init();
	void Update();
	void Draw();
};
