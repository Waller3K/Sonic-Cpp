#include <iostream>
#include <SFML/Window.hpp>

#include "MenuScene.hpp"
#include "IDs.hpp"

MenuScene::MenuScene(GameEngine* g)
    : Scene(g)
{

}

void MenuScene::init()
{
    std::cout << "MenuScene!" << std::endl;
    registerAction(static_cast<int>(sf::Keyboard::Key::Enter), static_cast<int>(ActionIDs::SWITCH_SCENES));
}

void MenuScene::update()
{

}

void MenuScene::onEnd()
{
    std::cout << "Switching Scenes!" << std::endl;
}

void MenuScene::sRender()
{
    m_game->window().clear(sf::Color::Blue);

    m_game->window().display();
}

void MenuScene::sDoAction(Action a)
{
    if(a.getType() == false)
    {
        return;
    }
    if(a.getID() == static_cast<int>(ActionIDs::SWITCH_SCENES))
    {
        m_game->setScene(static_cast<int>(SceneIDs::GAME));
    }
}