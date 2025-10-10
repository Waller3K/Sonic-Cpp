#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

#include "Scene.hpp"

class GameEngine
{
	//Variable initialization
	std::map<int, std::shared_ptr<Scene>>		m_scenes;
	int 										m_currentScene;
	std::string									m_windowName	= "WallerEngine";
	sf::Vector2u								m_resolution 	= {1080, 720};
	sf::RenderWindow							m_window;
	bool										m_hasQuit		= false;
	bool										m_isRunning 	= false;
	sf::Clock									m_timeElapsed;	//A Clock that will show the total time the game has been running
	sf::Clock									m_deltaClock;	//A Clock that will be reset at the end of each frame
	sf::Time									m_deltaTime		= sf::Time::Zero;	//The time it took for the last frame to complete


public:

	GameEngine();
	GameEngine(sf::Vector2f resolution, std::string& windowName);
	void 					init(int defaultSceneID);
	void 					update();
	void 					sUserInput();
	void					setScene(int id);
	void 					addScene(int id, std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> 	getScene(int id);
	std::shared_ptr<Scene>	currentScene();
	void 					draw();
	void 					quit();
	sf::RenderWindow&		window();
	sf::Time				currentTime();
	sf::Time				deltaTime();


};
