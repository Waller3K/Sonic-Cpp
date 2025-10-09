#include "GameScene.hpp"
#include "IDs.hpp"

GameScene::GameScene(GameEngine* g)
    :   Scene(g)
{
}

void GameScene::init()
{
    std::cout << "GameScene!" << std::endl;
    registerAction(static_cast<int>(sf::Keyboard::Key::Enter), static_cast<int>(ActionIDs::SWITCH_SCENES));
}

void GameScene::update()
{

}

void GameScene::onEnd()
{
    std::cout << "Switching Scenes!" << std::endl;
}

void GameScene::sRender()
{
    m_game->window().clear(sf::Color::Red);

    m_game->window().display();
}

void GameScene::sDoAction(Action a)
{
    if(a.getType() == false)
    {
        return;
    }
    if(a.getID() == static_cast<int>(ActionIDs::SWITCH_SCENES))
    {
        m_game->setScene(static_cast<int>(SceneIDs::MENU));
    }
}