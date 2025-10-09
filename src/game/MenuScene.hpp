#include <Scene.hpp>
#include <EntityManager.hpp>
#include <GameEngine.hpp>
#include <Action.hpp>

class MenuScene : public Scene
{
public:

    MenuScene(GameEngine* g);

    void init();
    void update();
    void onEnd();
    void sDoAction(Action a); 
    void sRender();

};