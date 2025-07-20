#pragma once
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "common/ExplicitSingleton.h"

class TextureManager : public ExplicitSingleton<TextureManager> {
public:
	sf::Texture& get(std::string name);
	TextureManager();
private:
	std::map<std::string, sf::Texture*> textures;

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};