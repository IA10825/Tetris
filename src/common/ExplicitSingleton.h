#pragma once

template<class Type>
class ExplicitSingleton {
public:
	static Type& Ref() {
		static Type instance;
		return instance;
	}
	static const Type& CRef() {
		return Ref();
	}
};