#include "GameEngine.hpp"

GameEngine::GameEngine()
{

}

void GameEngine::Init()
{
		sf::Window window(sf::VideoMode({1080, 720}), "Sonic C++");
	


	while(window.isOpen())
	{
		while(const std::optional event = window.pollEvent())
		{
			if(event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}
	}

}

void GameEngine::Draw()
{

}

void GameEngine::Update()
{

}
