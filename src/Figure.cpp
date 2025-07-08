#include "Figure.h"
#include <iostream>

Figure::Figure(std::bitset<64> blueprint) {
	this->blueprint = blueprint;
}