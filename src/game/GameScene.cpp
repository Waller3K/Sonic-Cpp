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

    registerAction(static_cast<int>(sf::Keyboard::Key::Enter),  ActionIDs::SWITCH_SCENES);
    registerAction(static_cast<int>(sf::Keyboard::Key::W),      ActionIDs::UP);
    registerAction(static_cast<int>(sf::Keyboard::Key::S),      ActionIDs::DOWN);
    registerAction(static_cast<int>(sf::Keyboard::Key::A),      ActionIDs::LEFT);
    registerAction(static_cast<int>(sf::Keyboard::Key::D),      ActionIDs::RIGHT);

    //Initialized Player Entity
    m_player = m_entityManager.addEntity("Player");
    m_player->addComponent<CAnimation>(m_assets.getAnimation("SonicIdle"), true, 10);
    m_player->addComponent<CTransform>(sf::Vector2f({ 100.f, 100.f }));
    m_player->addComponent<CPlayerController>();
}

void GameScene::update()
{
    m_entityManager.update();
    sPlayerController();
}

void GameScene::onEnd()
{
    std::cout << "Switching Scenes!" << std::endl;
}

void GameScene::sRender()
{
    m_game->window().clear(sf::Color::Black);

    for(auto e : m_entityManager.getEntities())
    {
        if(!e->hasComponent<CAnimation>())
        {
            std::cerr << "CAnimation not found" << std::endl;
            return;
        }
        if(!e->hasComponent<CTransform>())
        {
            std::cerr << "CTransform not found" << std::endl;
            return;
        }

        e->getComponent<CAnimation>().animation->getSprite().setPosition(e->getComponent<CTransform>().pos);
        m_game->window().draw(e->getComponent<CAnimation>().animation->getSprite());

    }

}

void GameScene::sDoAction(Action a)
{
    if(a.getType() == false)
    {
        switch(a.getID())
        {
            case ActionIDs::UP:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().up = false;
                    }
                }
            break;

            case ActionIDs::DOWN:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().down = false;
                    }
                }
            break;

            case ActionIDs::LEFT:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().left = false;
                    }
                }
            break;

            case ActionIDs::RIGHT:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().right = false;
                    }
                }
            break;

            default:
            
            break;
        }

        return;
    }
    switch(a.getID())
    {
        case ActionIDs::SWITCH_SCENES:
            m_game->setScene(SceneIDs::MENU);
        break;

        case ActionIDs::UP:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().up = true;
                }
            }
        break;

        case ActionIDs::DOWN:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().down = true;
                }
            }
        break;

        case ActionIDs::LEFT:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().left = true;
                }
            }
        break;

        case ActionIDs::RIGHT:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().right = true;
                }
            }
        break;

        default:
        
        break;
    }
}

void GameScene::sPlayerController()
{
    for(auto e : m_entityManager.getEntities())
    {
        if(!e->hasComponent<CTransform>())
        {
            return;
        }
        if(!e->hasComponent<CPlayerController>())
        {
            return;
        }

        if(e->getComponent<CPlayerController>().up)
        {
            e->getComponent<CTransform>().pos.y -= 1;
        }
        
        if(e->getComponent<CPlayerController>().down)
        {
            e->getComponent<CTransform>().pos.y += 1;
        }
        
        if(e->getComponent<CPlayerController>().left)
        {
            e->getComponent<CTransform>().pos.x -= 1;
        }
        
        if(e->getComponent<CPlayerController>().right)
        {
            e->getComponent<CTransform>().pos.x += 1;
        }

    }
}