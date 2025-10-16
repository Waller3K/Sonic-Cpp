#include <GameEngine.hpp>
#include <Scene.hpp>
#include <EntityManager.hpp>
#include <Assets.hpp>
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>

class GameScene : public Scene
{

    EntityManager               m_entityManager;
    Assets                      m_assets;
    std::shared_ptr<Entity>     m_player;
    sf::View                    m_camera;

    //Temp camera controls
    bool m_cUp      = false;
    bool m_cDown    = false;
    bool m_cLeft    = false;
    bool m_cRight   = false;

public:
    GameScene(GameEngine* g);

    void init();
    void update();
    void onEnd();

    //Systems

    void sImGUI();
    void sDrawGrid();
    void sDoAction(Action a); 
    void sRender();
    void sPlayerController();
    void sAnimationUpdate();

    //Temp Camera Controller
    void sTempCameraControls();

};