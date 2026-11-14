#include <iostream>
#include <memory>
#include "vector2.h"
#include "stack_1.h"

int main() {
	std::unique_ptr<Stack<vector2_t<int>>> vector_stack = std::make_unique<Stack<vector2_t<int>>>();

	vector_stack->push(vector2_t<int>(10, 20, (char*)"VectorA"));
	vector_stack->push(vector2_t<int>(30, 40, (char*)"VectorB"));
	vector_stack->push(vector2_t<int>(50, 60, (char*)"VectorC"));

	std::cout << "Stack size: " << vector_stack->get_size() << std::endl;

	vector2_t<int> v = vector_stack->peek();
	std::cout << "Top vector: " << v << std::endl;
	std::cout << "v[0] (x) = " << v[0] << std::endl;
	std::cout << "v[1] (y) = " << v[1] << std::endl;

	v[0] = 99;
	std::cout << "After v[0] = 99: " << v << std::endl;

	try {
		std::cout << v[2] << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}
