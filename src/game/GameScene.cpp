#include <SFML/Graphics.hpp>

#include "GameScene.hpp"
#include "IDs.hpp"


GameScene::GameScene(GameEngine* g)
    :   Scene(g)
{
}

void GameScene::init()
{
    std::cout << "GameScene!" << std::endl;

    //Initialize Assets
    m_assets.initAssets("Assets.json");

    registerAction(static_cast<int>(sf::Keyboard::Key::Enter), ActionIDs::SWITCH_SCENES);

    //Initialized Player Entity
    m_player = m_entityManager.addEntity("Player");
    /*m_player->addComponent<CAnimation>(m_assets.getAnimation("Sonic"), false);
    m_player->addComponent<CTransform>(sf::Vector2f({ 100.f, 100.f }));*/
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
    m_game->window().clear(sf::Color::Black);

    sf::Sprite testSprite(m_assets.getTexture("Sonic"));

    testSprite.setPosition({ 100.f, 100.f });

    m_game->window().draw(testSprite);

    /*for(auto e : m_entityManager.getEntities())
    {
        if(!e->hasComponent<CAnimation>())
        {
            return;
        }
        if(!e->hasComponent<CTransform>())
        {
            return;
        }

        e->getComponent<CAnimation>().animation->getSprite().setPosition(e->getComponent<CTransform>().pos);
        m_game->window().draw(e->getComponent<CAnimation>().animation->getSprite());

    }*/

}

void GameScene::sDoAction(Action a)
{
    if(a.getType() == false)
    {
        return;
    }
    if(a.getID() == SWITCH_SCENES)
    {
        m_game->setScene(SceneIDs::MENU);
    }
}