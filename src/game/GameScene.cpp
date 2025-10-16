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

    registerAction(static_cast<int>(sf::Keyboard::Key::Enter),      ActionIDs::SWITCH_SCENES);
    registerAction(static_cast<int>(sf::Keyboard::Key::Up),         ActionIDs::DEBUG_UP);
    registerAction(static_cast<int>(sf::Keyboard::Key::Down),       ActionIDs::DEBUG_DOWN);
    registerAction(static_cast<int>(sf::Keyboard::Key::Left),       ActionIDs::DEBUG_LEFT);
    registerAction(static_cast<int>(sf::Keyboard::Key::Right),      ActionIDs::DEBUG_RIGHT);
    registerAction(static_cast<int>(sf::Keyboard::Key::W),          ActionIDs::CAMERA_UP);
    registerAction(static_cast<int>(sf::Keyboard::Key::S),          ActionIDs::CAMERA_DOWN);
    registerAction(static_cast<int>(sf::Keyboard::Key::A),          ActionIDs::CAMERA_LEFT);
    registerAction(static_cast<int>(sf::Keyboard::Key::D),          ActionIDs::CAMERA_RIGHT);

    //Initialized Camera View
    m_camera = sf::View({240.0f, 135.0f}, {480.0f, 270.0f});

    m_game->window().setView(m_camera);

    //Initialized Player Entity
    m_player = m_entityManager.addEntity("Player");
    m_player->addComponent<CAnimation>(m_assets.getAnimation("SonicIdle"), true, 20);
    m_player->addComponent<CTransform>(sf::Vector2f({ 0.f,0.f }));
    m_player->addComponent<CPlayerController>();
}

void GameScene::update()
{
    m_entityManager.update();
    sPlayerController();
    sAnimationUpdate();
    sTempCameraControls();
    sImGUI();
}

void GameScene::onEnd()
{
    for(auto e : m_entityManager.getEntities())
    {
        e->distroy();
    }

    m_game->resetCamera();

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

        e->getComponent<CAnimation>().animation->getSprite().setPosition(e->getComponent<CTransform>().pos - m_camera.getCenter());
        m_game->window().draw(e->getComponent<CAnimation>().animation->getSprite());

    }

}

void GameScene::sDrawGrid()
{
    int gridSize = 64;

    sf::Vector2u windowDimensions = m_game->window().getSize();

    sf::Vector2f offset = m_camera.getCenter();

    int numCols = floor(windowDimensions.x / gridSize);
	int numRows = floor(windowDimensions.y / gridSize);

	int numOfCells = numCols * numRows;

    //Vertical Lines
    for (int i = 0; i < numCols; i++)
	{
		//Each line is made of two vertices
		sf::VertexArray line(sf::PrimitiveType::Lines, 2);

		//Sets the positions of the two vertices
		line[0].position = sf::Vector2f({ static_cast<float>(i * gridSize), 0.0f });
		line[1].position = sf::Vector2f({ static_cast<float>(i * gridSize), static_cast<float>(windowDimensions.y) });

		//sets the color of the line
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;

		m_game->window().draw(line);
	}

    //Horizontal Lines
    for (int i = 0; i < numRows; i++)
	{
		//Each line is made of two vertices
		sf::VertexArray line(sf::PrimitiveType::Lines, 2);

		//Sets the positions of the two vertices
		line[0].position = sf::Vector2f({ 0.0f, static_cast<float>(i * gridSize) });
		line[1].position = sf::Vector2f({ static_cast<float>(windowDimensions.x), static_cast<float>(i * gridSize) });
		
		//sets the color of the line
		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;
		
		m_game->window().draw(line);
	}


}

void GameScene::sTempCameraControls()
{
    if(m_cUp)
    {
        m_camera.move({0.0, -1.0});
    }
    if(m_cDown)
    {
        m_camera.move({0.0, 1.0});
    }
    if(m_cLeft)
    {
        m_camera.move({-1.0, 0.0});
    }
    if(m_cRight)
    {
        m_camera.move({1.0, 0.0});
    }
}

void GameScene::sImGUI()
{
    ImGui::Begin("Debug Menu");
        ImGui::Checkbox("Camera Up", &m_cUp);
        ImGui::Text("Info!");
        ImGui::BeginChild("Scrolling");
            ImGui::Text("Camera Position: %f, %f", m_camera.getCenter().x, m_camera.getCenter().y);
            for(auto e : m_entityManager.getEntities())
            {
                if(!e->hasComponent<CTransform>())
                {
                    return;
                }
                ImGui::Text("Entity's Position: %f, %f", e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
            }
        ImGui::EndChild();
    ImGui::End();
}

void GameScene::sDoAction(Action a)
{
    //If the key is released
    if(a.getType() == false)
    {
        switch(a.getID())
        {

            case ActionIDs::CAMERA_UP:
                m_cUp = false;
            break;

            case ActionIDs::CAMERA_DOWN:
                m_cDown = false;
            break;

            case ActionIDs::CAMERA_LEFT:
                m_cLeft = false;
            break;

            case ActionIDs::CAMERA_RIGHT:
                m_cRight = false;
            break;

            case ActionIDs::DEBUG_UP:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().up = false;
                    }
                }
            break;

            case ActionIDs::DEBUG_DOWN:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().down = false;
                    }
                }
            break;

            case ActionIDs::DEBUG_LEFT:
                for (auto e : m_entityManager.getEntities())
                {
                    if(e->hasComponent<CPlayerController>())
                    {
                        e->getComponent<CPlayerController>().left = false;
                    }
                }
            break;

            case ActionIDs::DEBUG_RIGHT:
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

    //If the key is pressed
    switch(a.getID())
    {
        case ActionIDs::SWITCH_SCENES:
            m_game->setScene(SceneIDs::MENU);
        break;

        case ActionIDs::CAMERA_UP:
            m_cUp = true;
        break;

        case ActionIDs::CAMERA_DOWN:
            m_cDown = true;
        break;

        case ActionIDs::CAMERA_LEFT:
            m_cLeft = true;
        break;

        case ActionIDs::CAMERA_RIGHT:
            m_cRight = true;
        break;

        case ActionIDs::DEBUG_UP:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().up = true;
                }
            }
        break;

        case ActionIDs::DEBUG_DOWN:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().down = true;
                }
            }
        break;

        case ActionIDs::DEBUG_LEFT:
            for (auto e : m_entityManager.getEntities())
            {
                if(e->hasComponent<CPlayerController>())
                {
                    e->getComponent<CPlayerController>().left = true;
                }
            }
        break;

        case ActionIDs::DEBUG_RIGHT:
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

void GameScene::sAnimationUpdate()
{
    for(auto e : m_entityManager.getEntities())
    {
        if(!e->hasComponent<CAnimation>())
        {
            return;
        }

        if(!e->getComponent<CAnimation>().isAnimated)
        {
            return;
        }

        if(e->getComponent<CAnimation>().iterator < e->getComponent<CAnimation>().animSpd)
        {
            e->getComponent<CAnimation>().iterator++;
        }
        else
        {
            e->getComponent<CAnimation>().animation->update();
            e->getComponent<CAnimation>().iterator = 0;
        }
        

    }
}