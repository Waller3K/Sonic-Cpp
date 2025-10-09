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

	setScene(defaultSceneID);

	update();
}

void GameEngine::draw()
{
	currentScene()->sRender();
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
		currentScene()->update();
		draw();
	}
}

void GameEngine::sUserInput()
{
	//Checks to see if the window's x has been pressed.
	while(const std::optional event = m_window.pollEvent())
	{
		if(event->is<sf::Event::Closed>())
		{
			quit();
		}

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
	currentScene()->onEnd();
	m_isRunning = false;
	m_window.close();
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}
