// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "tuple.h"
#include "utils/mpl.h"


int main(int, char**) {
	Tuple2<int, float> a;

	get<0>(a) = -154;
	get<1>(a) = 331.234;

	const auto b = a;

	//get<1>(b) = 1.5f; // error, b is const


	std::cout << get<0>(b) << " " << get<1>(b) << std::endl;


	return 0;
}

