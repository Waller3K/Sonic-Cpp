#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class Components
{
public:
    bool has = false;
};

class CTransform : public Components
{
public:
    sf::Vector2f    pos;
    sf::Vector2f    prevPos;

    sf::Vector2f    scale;
    sf::Vector2f    velocity;
    float           angle;

    CTransform(){}
    CTransform(const sf::Vector2f& p)
        : pos(p) {}
    CTransform(const sf::Vector2f& p, const sf::Vector2f& v, const float a)
        : pos(p), velocity(v), angle(a) {}
};

class CAnimation : public Components
{

public:
    std::shared_ptr<Animation> animation;
    bool repeat = false;
    int animSpd = 0;
    bool isAnimated = false;
    int iterator = 0;

    CAnimation(){}
    //For Still Sprites
    CAnimation(std::shared_ptr<Animation> a)
        :   animation(a) {}

    //For Animated Sprites
    CAnimation(std::shared_ptr<Animation> a, bool r, int s)
        :   animation(a), repeat(r), animSpd(s), isAnimated(true) {}

};

class CPlayerController : public Components
{

public:

    CPlayerController(){}
    
    //Temp Controls
    bool up     = false;
    bool down   = false;
    bool left   = false;
    bool right  = false;

};

class CGravity : public Components
{

public:
    float gravity = 0.0f;

    CGravity(){}
    CGravity(float g)
        :   gravity(g) {}

};

class CSlopeCollider : public Components
{

public:

    CSlopeCollider(){}

};