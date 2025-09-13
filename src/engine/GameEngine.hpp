#pragma once

#include <SFML/Graphics.hpp>

class GameEngine
{
	sf::Vector2i resolution = {1080, 720};
public:
	GameEngine();
	void Init();
	void Update();
	void Draw();
};
