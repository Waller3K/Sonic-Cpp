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
    std::unique_ptr<Animation> animation;
    bool repeat = false;


    CAnimation(){}
    CAnimation(std::unique_ptr<Animation> a, bool r)
        :   animation(std::move(a)), repeat(r) {}

};

class CPlayerController : public Components
{

public:

    CPlayerController(){}

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