#include <GameEngine.hpp>
#include <Scene.hpp>
#include <EntityManager.hpp>

class GameScene : public Scene
{
    EntityManager m_entityManager;
public:
    GameScene(GameEngine* g);

    void init();
    void update();
    void onEnd();
    void sDoAction(Action a); 
    void sRender();

};