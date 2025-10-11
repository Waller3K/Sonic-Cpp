#pragma once

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp>

#include "Animation.hpp"

class Assets
{
	std::map<std::string, std::unique_ptr<sf::Texture>>		m_textures;
	std::map<std::string, std::shared_ptr<Animation>>		m_animations; //Uses shared_ptr because multiple objects require ownership
	std::map<std::string, sf::SoundBuffer>					m_sounds;
	std::map<std::string, std::unique_ptr<sf::Music>>		m_music;
	std::map<std::string, sf::Font>							m_fonts;
	nlohmann::json											m_assetJson;

public:
	Assets() {}

	void initAssets(std::string path);
	void addTexture(const std::string& name, const std::string& path);
	void addAnimation(const std::string& name, std::shared_ptr<Animation> a);
	void addSoundBuffer(std::string& name, std::string& path);
	void addMusic(std::string& name, std::string& path, bool loop);
	void addFont(std::string& name, std::string& path);

	sf::Texture& getTexture(const std::string& name);
	std::shared_ptr<Animation> getAnimation(const std::string name);
	sf::SoundBuffer getSoundBuffer(std::string name);
	std::unique_ptr<sf::Music>& getMusic(std::string name);
	sf::Font& getFont(std::string name);
};