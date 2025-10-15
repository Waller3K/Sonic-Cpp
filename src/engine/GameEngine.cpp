#include <imgui.h>
#include <imgui-SFML.h>

#include "GameEngine.hpp"

GameEngine::GameEngine()
	: m_isRunning(true)
{ 
}

GameEngine::GameEngine(sf::Vector2f resolution, std::string& windowName)
	: 	m_isRunning(true),
		m_resolution(resolution),
		m_windowName(windowName)
{	
}

void GameEngine::init(int defaultSceneID)
{
	m_window.create(sf::VideoMode(m_resolution), m_windowName);

	m_window.setKeyRepeatEnabled(false);

	m_window.setFramerateLimit(180);

	m_defaultCam = sf::View(sf::Vector2f{static_cast<float>(m_resolution.x/2), static_cast<float>(m_resolution.y/2)}, static_cast<sf::Vector2f>(m_resolution));

	m_window.setView(m_defaultCam);

	if(!ImGui::SFML::Init(m_window)){
		std::cerr << "ImGui Failed to Initialize" << std::endl; 
		quit();
		return; 
	}

	setScene(defaultSceneID);

	update();
}

void GameEngine::draw()
{
	currentScene()->sRender();
	ImGui::SFML::Render(window());
	window().display();
}

void GameEngine::setScene(int id)
{

	//Runs the onEnd function of the current scene if there is one
	if(currentScene())
	{
		currentScene()->onEnd();
	}

	m_currentScene = id;

	currentScene()->init();
}

void GameEngine::addScene(int id, std::shared_ptr<Scene> scene)
{
	m_scenes[id] = scene;
}

std::shared_ptr<Scene> GameEngine::getScene(int id)
{
	return m_scenes[id];
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_scenes[m_currentScene];
}

void GameEngine::update()
{
	while(m_isRunning)
	{
		sUserInput();
		ImGui::SFML::Update(window(), deltaTime());
		currentScene()->update();
		draw();
		//Restarts the delta clock at the end of each frame, and stores the elapsed time in m_deltaTime
		m_deltaTime = m_deltaClock.restart(); 

		if(m_hasQuit)
		{
			quit();
			return;
		}
	}
}

void GameEngine::resetCamera()
{
    m_window.setView(m_defaultCam);
}

void GameEngine::sUserInput()
{
	
	while(const std::optional event = m_window.pollEvent())
	{
		//Checks to see if the window's x has been pressed.
		if(event->is<sf::Event::Closed>())
		{
			m_hasQuit = true;
			return;
		}

		ImGui::SFML::ProcessEvent(window(), *event);

		if(const auto& keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if(currentScene()->getActionMap().find(static_cast<int>(keyPressed->code)) == currentScene()->getActionMap().end())
			{
				continue;
			}

			const bool actionType = true; //This is the new version of the START action type

			Action a(currentScene()->getActionMap().at(static_cast<int>(keyPressed->code)), actionType);

			currentScene()->sDoAction(a);

		}

		if(const auto& keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			if(currentScene()->getActionMap().find(static_cast<int>(keyReleased->code)) == currentScene()->getActionMap().end())
			{
				continue;
			}

			const bool actionType = false; //This is the new version of the END action type

			Action a(currentScene()->getActionMap().at(static_cast<int>(keyReleased->code)), actionType);

			currentScene()->sDoAction(a);
		}

	}
}

void GameEngine::quit()
{

	ImGui::SFML::Shutdown();
	
	if(currentScene())
	{
		currentScene()->onEnd();
	}
	m_isRunning = false;

	m_window.close();
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}

sf::Time GameEngine::currentTime()
{
	return m_timeElapsed.getElapsedTime();
}

sf::Time GameEngine::deltaTime()
{
	return m_deltaTime;
}
