#include <GameEngine.hpp>
#include <Scene.hpp>
#include <EntityManager.hpp>
#include <Assets.hpp>
#include <vector>

class GameScene : public Scene
{

    EntityManager               m_entityManager;
    Assets                      m_assets;
    std::shared_ptr<Entity>     m_player;


public:
    GameScene(GameEngine* g);

    void init();
    void update();
    void onEnd();
    void sDoAction(Action a); 
    void sRender();
    void sPlayerController();
    void sAnimationUpdate();

};