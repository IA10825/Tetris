#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>

class Grid;

class Figure {
public:
	enum Type {
		EMPTY, J, I, O, L, Z, T, S
	};
	Figure(std::bitset<64>, Type);
	Type getType() const;
	std::bitset<16> getFrame(unsigned rotation) const;
private:
	std::bitset<64> blueprint;
	Type type;
};