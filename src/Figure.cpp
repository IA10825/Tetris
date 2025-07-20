#include "Figure.h"
#include <iostream>

Figure::Figure(std::bitset<64> blueprint, Type type) {
	if (type == Figure::EMPTY) throw std::invalid_argument("Figure type cannot be EMPTY");
	this->blueprint = blueprint;
	this->type = type;
}

Figure::Type Figure::getType() const {
	return type;
}

std::bitset<16> Figure::getFrame(unsigned r) const {
	if (r > 3) throw std::out_of_range("Rotation out of range");
	std::bitset<64> mask;
	for (int i = 0; i < 64; i++) {
		mask.set(i, (i / 16) == (3 - r));
	}

	return std::bitset<16>(((blueprint & mask) >> 16 * (3-r)).to_ulong());
}