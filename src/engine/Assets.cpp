#include <nlohmann/json.hpp>
#include <fstream>
#include <memory>
#include <iostream>

#include "Assets.hpp"

void Assets::initAssets(std::string path)
{
	//loads the Assets.json file
	std::fstream assetJsonFileStream(path);
	m_assetJson = nlohmann::json::parse(assetJsonFileStream);

	for (auto& [key, val] : m_assetJson.items())
	{
		if (key == "Textures")
		{
			for (auto& [k2, v2] : m_assetJson["Textures"].items())
			{
				std::string name = k2;
				std::string path = v2;

				addTexture(name, path);
			}
		}
		else if (key == "Fonts")
		{
			for (auto& [k, v] : m_assetJson["Fonts"].items())
			{
				std::string name = k;
				std::string path = v;
				addFont(name, path);
			}
		}
		else if (key == "SFX")
		{
			for (auto& [k, v] : m_assetJson["SFX"].items())
			{
				std::string name = k;
				std::string path = v;
				addSoundBuffer(name, path);
			}
		}
		else if (key == "Music")
		{
			for (auto& [k, v] : m_assetJson["Music"].items())
			{
				std::string name = k;
				std::string path;
				bool loop = false;
				for (auto& [k2, v2] : m_assetJson["Music"][k].items())
				{
					if (k2 == "Path")
					{
						path = v2;
					}
					else if (k2 == "Loop")
					{
						loop = v2;
					}
				}
				addMusic(name, path, loop);
			}
		}
	}

	//Animations are a bit more complex, so we will handle them seperately
	for (auto& [key, val] : m_assetJson.items()) 
	{
		if (key == "Animations")
		{
			for (auto& [k2, v2] : m_assetJson["Animations"].items())
			{
				std::string tName;
				std::string animName = k2;
				int frameCount = 0;
				int animSpd = 0;
				const sf::Texture* t = nullptr;

				for (auto& [k, v] : m_assetJson["Animations"][k2].items())
				{
					if (k == "Texture")
					{
						tName = v;
						t = &getTexture(tName);
						//sf::Texture tex("Assets\\Default\\Null_Texture.png");
						//t = tex;
					}
					else if (k == "FrameCount")
					{
						frameCount = v;
					}
					else if (k == "AnimSpd")
					{
						animSpd = v;
					}
				}

				std::shared_ptr<Animation> a = std::make_shared<Animation>(animName, t, frameCount, animSpd);
				addAnimation(animName, a);
			}
		}
	}
}

void Assets::addTexture(const std::string& name, const std::string& path)
{
	if (m_textures.count(name)) 
	{
		std::cerr << "Texture with name " << name << " already exists, skipping load." << std::endl;
		return;
	}
	
	auto t = std::make_unique<sf::Texture>();
	if (!t->loadFromFile(path)) 
	{
		std::cerr << "Could not load texture from: " << path << std::endl;
		return;
	}
	std::cout << "Loaded " << path << " successfully!" << std::endl;
	m_textures[name] = std::move(t);

	/*sf::Texture t(path);
	m_textures[name] = t;
	std::cout << "Loaded " << path << " successfully!" << std::endl;*/
}

void Assets::addAnimation(const std::string& name, std::shared_ptr<Animation> a)
{
	std::cout << "Loaded Animation: " << a->getName() << " successfully!" << std::endl;
	m_animations[name] = a;
}

void Assets::addSoundBuffer(std::string& name, std::string& path)
{
	//Sounds are loaded into a sound buffer
	sf::SoundBuffer b;
	
	if (!b.loadFromFile(path)) 
	{
		std::cerr << "Could not load sound file from: " << path << std::endl;
		return;
	}

	//We then push that sound buffer to the map under the name given into the function arguments
	m_sounds[name] = b;
}

void Assets::addMusic(std::string& name, std::string& path, bool loop)
{
	auto m = std::make_unique<sf::Music>();

	m->setLooping(loop);

	if (m->openFromFile(path)) 
	{
		m_music[name] = std::move(m); //Because 'm' is a unique pointer, we have to use std::move to put it in the map.
		std::cout << "Loaded " << path << " successfully!" << std::endl;
	}
	else 
	{
		std::cerr << "Could not load music file from: " << path << std::endl;
		return;
	}
}

void Assets::addFont(std::string& name, std::string& path)
{
	sf::Font f;

	if (!f.openFromFile(path)) 
	{
		std::cerr << "Could not load font file from: " << path << std::endl;
		return;
	}

	m_fonts[name] = f;
	std::cout << "Loaded " << path << " successfully!" << std::endl;
}

sf::Texture& Assets::getTexture(const std::string& name)
{

	auto it = m_textures.find(name);
	if (it != m_textures.end()) 
	{
		return *(it->second);
	}
	else 
	{
		std::cerr << "Texture " << name << " not found!" << std::endl;
		return *(m_textures["Default"]);
	}

	/*if (m_textures.find(name) == m_textures.end()) 
	{
		std::cerr << "Texture " << name << " not found!" << std::endl;
		return m_textures["Default"];
	}
	return m_textures[name];*/
}

std::shared_ptr<Animation> Assets::getAnimation(const std::string name)
{
	if (m_animations.find(name) == m_animations.end()) 
	{
		std::cerr << "Animation " << name << " not found!" << std::endl;
		return m_animations["Default"];
	}
	return m_animations[name];
}

sf::SoundBuffer Assets::getSoundBuffer(std::string name)
{
	return m_sounds[name];
}

std::unique_ptr<sf::Music>& Assets::getMusic(std::string name)
{
	return m_music[name];
}

sf::Font& Assets::getFont(std::string name)
{
	return m_fonts[name];
}
