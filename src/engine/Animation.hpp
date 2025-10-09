#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Animation
{
    std::string			m_name = "null";
	sf::Texture			m_defaultTexture;	//A default texture to use if no texture is given
	const sf::Texture*	m_texture = nullptr; //Pointer to a texture in the assets manager
	sf::Sprite			m_sprite;
	size_t				m_frameCount = 0;
	size_t				m_currentFrame = 0;
	size_t				m_playbackSpeed = 0;
    sf::Vector2f        m_size;

public:
    Animation();
	Animation(const std::string& name, const sf::Texture* t);
	Animation(const std::string& name, const sf::Texture* t, size_t frameCount, size_t speed);

	void update();
	const sf::Vector2f& getSize() const;
	const std::string& getName() const;
	const sf::Texture* getTexture() const;
	sf::Sprite& getSprite();
	bool hasEnded() const;
};