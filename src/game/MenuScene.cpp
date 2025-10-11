#include <iostream>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "MenuScene.hpp"
#include "IDs.hpp"

MenuScene::MenuScene(GameEngine* g)
    :   Scene(g),
        m_ImGuiToggle(true)
{

}

void MenuScene::init()
{
    std::cout << "MenuScene!" << std::endl;
    registerAction(static_cast<int>(sf::Keyboard::Key::Enter), ActionIDs::SWITCH_SCENES);
}

void MenuScene::update()
{

    //ImGui Section

    ImGui::Begin("Sonic C++", &m_ImGuiToggle);
    if(ImGui::Button("Start Game!"))
    {
        m_game->setScene(SceneIDs::GAME);
    }
    ImGui::End();
}

void MenuScene::onEnd()
{
    std::cout << "Switching Scenes!" << std::endl;
}

void MenuScene::sRender()
{
    m_game->window().clear(sf::Color::Blue);
}

void MenuScene::sDoAction(Action a)
{
    if(a.getType() == false)
    {
        return;
    }
    if(a.getID() == ActionIDs::SWITCH_SCENES)
    {
        m_game->setScene(SceneIDs::GAME);
    }
}