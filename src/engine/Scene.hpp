#pragma once

#include <map>

#include "Action.hpp"

class GameEngine;

class Scene
{
protected:
    GameEngine*                  m_game;
    int                          m_currentFrame;
    std::map<int, int>           m_actionMap; // Maps input keys to action IDs
    bool                         m_isPaused;
    bool                         m_hasEnded;

public:
    
    Scene(GameEngine* g);

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void onEnd() = 0;
    virtual void sDoAction(Action a) = 0; // Changed to take action ID
    virtual void sRender() = 0;

    void simulate(int num);
    const std::map<int, int>& getActionMap(); // Changed to return map of input keys to action IDs
    void registerAction(int input, int actionID); // Changed to take action ID


};