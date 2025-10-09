#pragma once

#include <SFML/Graphics.hpp>


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