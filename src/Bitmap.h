#pragma once
#include <iostream>

namespace Misc {
	template<unsigned L>
	class Bitmap {
	public:
		Bitmap(std::uint64_t string) {
			data = string;
		};

		bool operator[](unsigned i) {
			
		}

		std::ostream& operator<<(std::ostream& stream) {
			stream << data;
			return stream;
		}
	private:
		std::uint64_t data;
		unsigned length = L;
	};
}