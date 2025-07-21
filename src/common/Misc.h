#pragma once

namespace Misc {
	template<typename T>
	void swap(T& a, T& b) {
		T buffer = a;
		a = b;
		b = buffer;
	}
}