#include <iostream>

#include "Animation.hpp"

Animation::Animation()
	:	m_texture(nullptr),
		m_defaultTexture("Assets\\Default\\Null_Texture.png"),
		m_sprite(m_defaultTexture)
{

}

Animation::Animation(const std::string& name, const sf::Texture* t)
	:	m_name(name),
		m_texture(t),
		m_sprite(*t)
{
	m_size = sf::Vector2f(static_cast<float>(t->getSize().x), static_cast<float>(t->getSize().y));
	m_sprite.setOrigin({ m_size.x / 2.0f, m_size.y / 2.0f });
}

Animation::Animation(const std::string& name, const sf::Texture* t, size_t frameCount, size_t speed) 
	:	m_name(name),
		m_texture(t),
		m_sprite(*t),
		m_frameCount(frameCount),
		m_playbackSpeed(speed)
{
	m_size = sf::Vector2f(static_cast<float>(t->getSize().x) / frameCount, static_cast<float>(t->getSize().y));
	m_sprite.setOrigin({ m_size.x / 2.0f, m_size.y / 2.0f });
	m_sprite.setTextureRect(sf::IntRect({ static_cast<int>(std::floor(m_currentFrame) * m_size.x), 0 }, { static_cast<int>(m_size.x), static_cast<int>(m_size.y) }));
}

void Animation::update() 
{
	if(m_currentFrame < m_frameCount - 1)
	{
		m_currentFrame++;
	}
	else
	{
		m_currentFrame = 0;		
	}
	m_sprite.setTextureRect(sf::IntRect({ static_cast<int>(std::floor(m_currentFrame) * m_size.x), 0 }, { static_cast<int>(m_size.x), static_cast<int>(m_size.y) }));
}

const sf::Vector2f& Animation::getSize() const 
{
	return m_size;
}

const std::string& Animation::getName() const
{
	return m_name;
}

const sf::Texture* Animation::getTexture() const
{
	return m_texture;
}

sf::Sprite& Animation::getSprite()
{
	return m_sprite;
}

bool Animation::hasEnded() const 
{
	//TODO: detect when animation has ended (last frame was played) and return true
	return false;
}

