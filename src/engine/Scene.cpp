#include "Scene.hpp"
#include "GameEngine.hpp"

Scene::Scene(GameEngine* g)
    : m_game(g),
      m_currentFrame(0),
      m_isPaused(false),
      m_hasEnded(false)
{
}

void Scene::simulate(int num)
{
    for (int i = 0; i < num; i++) 
    {
        update();
    }
}

const std::map<int, int>& Scene::getActionMap()
{
    return m_actionMap;
}

void Scene::registerAction(int input, int actionID)
{
    m_actionMap[input] = actionID;
}