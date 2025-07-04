#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() {
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator("res")) {
		if (!(
			entry.path().extension().string() == ".png" ||
			entry.path().extension().string() == ".jpg" ||
			entry.path().extension().string() == ".jpeg"
			)) {
			std::cerr << typeid(*this).name() << ": Texture " << entry.path() << " - invalid file extension";
			continue;
		}
		sf::Texture* p = new sf::Texture;
		if (
			!(*p).loadFromFile(entry.path())
			) {
			std::cerr << typeid(*this).name() << ": Texture " << entry.path() << " could not be loaded";
			continue;
		}
		textures[entry.path().filename().stem().string()] = p;
	}
	textures["blank"] = new sf::Texture;
}

sf::Texture& TextureManager::get(std::string name) {
	if (textures[name]) {
		return *textures[name];
	}
	else {
		std::cerr << typeid(*this).name() << ": Texture " << name << " was not found";
		return *textures["blank"];
	}
}