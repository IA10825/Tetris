#include "Figure.h"
#include <iostream>

Figure::Figure(std::bitset<64> blueprint, Type type) {
	if (type == Figure::EMPTY) throw std::invalid_argument("Figure type cannot be EMPTY");
	this->blueprint = blueprint;
	this->type = type;
}