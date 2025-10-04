#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#include "Scene.hpp"

enum SceneID
{
	MENU	
};

class GameEngine
{
	//Variable initialization
	std::map<SceneID, std::shared_ptr<Scene>>	m_scenes;
	int 										m_currentScene;
	sf::Vector2u								m_resolution 	= {1080, 720};
	sf::RenderWindow							m_window;
	bool										m_isRunning 	= false;

public:

	GameEngine();
	void Init();
	void Update();
	void sUserInput();
	void Draw();
	void Quit();

};
