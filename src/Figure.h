#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>

class Grid;

struct Figure {
	enum Type {
		EMPTY, J, I, O, L, Z, T, S
	};
	Figure(std::bitset<64> blueprint);
	std::bitset<64> blueprint;
};