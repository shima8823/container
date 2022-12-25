#include "tester.hpp"

// printSubTitleの(1)などの数字はcppreferenceの関数番号に対応している

static void constructorTest() {
	printTitle("constructor");
	{
		printSubTitle("(1)");
		int_vector v;
		v.push_back(42);
		printVector(v);
	}
	{
		printSubTitle("(2)");
		std::allocator<int> alloc;
		int_vector v(alloc);
		v.push_back(42);
		printVector(v);
	}
	{
		printSubTitle("(3)");
		std::allocator<int> alloc;
		int_vector v(40, 42, alloc);
		printVector(v);
	}
	{
		printSubTitle("(5)");
		std::allocator<int> alloc;
		int_vector inputVector(40, 21);
		int_vector v(inputVector.begin(), inputVector.end());
		int_vector v_alloc(inputVector.begin(), inputVector.end(), alloc);
		printVector(v);
		printVector(v_alloc);
	}
	{
		printSubTitle("(6)");
		int_vector inputVector(40, 21);
		int_vector v(inputVector);
		printVector(v);
	}
}

static void assignTest() {
	printTitle("assign");
	{
		printSubTitle("operator=");
		int_vector inputVector(40, 21);
		int_vector v;
		v = inputVector;
		printVector(inputVector);
		printVector(v);
	}
	{
		printSubTitle("(1)");
		int_vector v;
		v.assign(40, 42);
		printVector(v);
	}
	{
		printSubTitle("(2)");
		int_vector inputVector(40, 21);
		int_vector v;
		v.assign(inputVector.begin(), inputVector.end());
		printVector(v);
	}
}

static void get_allocatorTest() {
	printTitle("get_allocator");
	std::allocator<int> alloc;
	int_vector v;
	printBool(v.get_allocator() == alloc);
}

static void atTest() {
	printTitle("at");
	{
		printSubTitle("not const");
		int_vector v(10, 42);
		std::cout << "v.at(3) = [" << v.at(3) << "]" << std::endl;
		v.at(3) = 21;
		printVector(v);
		try {
			v.at(10000);
		} catch (std::out_of_range const& exc) {
			std::cout << "out_of_range" << '\n';
		}
	}
	{
		printSubTitle("const");
		const int_vector v(10, 42);
		std::cout << "v.at(3) = [" << v.at(3) << "]" << std::endl;
		// v.at(3) = 21;
		try {
			v.at(10000);
		} catch (std::out_of_range const& exc) {
			std::cout << "out_of_range" << '\n';
		}
	}
}

static void operatorBracketTest() {
	printTitle("operator[]");
	{
		printSubTitle("not const");
		int_vector v(10, 42);
		std::cout << "v[3] = [" << v[3] << "]" << std::endl;
		v[3] = 21;
		printVector(v);
	}
	{
		printSubTitle("const");
		const int_vector v(10, 42);
		std::cout << "v[3] = [" << v[3] << "]" << std::endl;
		// v[3] = 21;
	}
}

static void frontTest() {
	printTitle("front");
	{
		printSubTitle("not const");
		int_vector v(10, 42);
		std::cout << "v.front() = [" << v.front() << "]" << std::endl;
		v.front() = 21;
		printVector(v);
	}
	{
		printSubTitle("const");
		const int_vector v(10, 42);
		std::cout << "v.front() = [" << v.front() << "]" << std::endl;
		// v.front() = 21;
	}
}

static void backTest() {
	printTitle("back");
	{
		printSubTitle("not const");
		int_vector v(10, 42);
		std::cout << "v.back() = [" << v.back() << "]" << std::endl;
		v.back() = 21;
		printVector(v);
	}
	{
		printSubTitle("const");
		const int_vector v(10, 42);
		std::cout << "v.back() = [" << v.back() << "]" << std::endl;
		// v.back() = 21;
	}
}

static void dataTest() {
	printTitle("data");
	{
		printSubTitle("not const");
		int_vector v;
		v.push_back(42); v.push_back(21); v.push_back(100000); v.push_back(-42);
		int* array = v.data();
		for (size_t i = 0; i < 4; i++)
		{
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
		array[2] = -21;
		printVector(v);
	}
	{
		printSubTitle("const");
		int_vector input_vector;
		input_vector.push_back(42); input_vector.push_back(21); input_vector.push_back(100000); input_vector.push_back(-42);
		const int_vector v(input_vector.begin(), input_vector.end());
		const int* array = v.data();
		for (size_t i = 0; i < 4; i++)
			std::cout << array[i] << " ";
		std::cout << std::endl;
		// array[2] = -21;
	}
}

static void iteratorsTest() {
	printTitle("iterators");
	{
		printSubTitle("begin not const");
		int_vector v;
		v.push_back(10000); v.push_back(21); v.push_back(-21); v.push_back(-42);
		int_vector::iterator it = v.begin();
		std::cout << "v.begin() = [" << *it << "]" << std::endl;
		*it = 42;
		printVector(v);
	}
	{
		printSubTitle("begin const");
		int_vector input_vector;
		input_vector.push_back(42); input_vector.push_back(21); input_vector.push_back(-21); input_vector.push_back(-42);
		const int_vector v(input_vector.begin(), input_vector.end());
		int_vector::const_iterator it = v.begin();
		std::cout << "v.begin() = [" << *it << "]" << std::endl;
		// *it = 21;
	}
	{
		printSubTitle("end not const");
		int_vector v;
		v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-10000);
		int_vector::iterator it = v.end() - 1;
		std::cout << "v.end() = [" << *it << "]" << std::endl;
		*it = -42;
		printVector(v);
	}
	{
		printSubTitle("end const");
		int_vector input_vector;
		input_vector.push_back(42); input_vector.push_back(21); input_vector.push_back(-21); input_vector.push_back(-42);
		const int_vector v(input_vector.begin(), input_vector.end());
		int_vector::const_iterator it = v.end() - 1;
		std::cout << "v.end() = [" << *it << "]" << std::endl;
		// *it = -21;
	}
	{
		printSubTitle("rbegin not const");
		int_vector v;
		v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-10000);
		int_vector::reverse_iterator it = v.rbegin();
		std::cout << "v.rbegin() = [" << *it << "]" << std::endl;
		*it = -42;
		printVector(v);
	}
	{
		printSubTitle("rbegin const");
		int_vector input_vector;
		input_vector.push_back(42); input_vector.push_back(21); input_vector.push_back(-21); input_vector.push_back(-42);
		const int_vector v(input_vector.begin(), input_vector.end());
		int_vector::const_reverse_iterator it = v.rbegin();
		std::cout << "v.rbegin() = [" << *it << "]" << std::endl;
		// *it = -21;
	}
	{
		printSubTitle("rend not const");
		int_vector v;
		v.push_back(10000); v.push_back(21); v.push_back(-21); v.push_back(-42);
		int_vector::reverse_iterator it = v.rend() - 1;
		std::cout << "v.rend() = [" << *it << "]" << std::endl;
		*it = 42;
		printVector(v);
	}
	{
		printSubTitle("rend const");
		int_vector input_vector;
		input_vector.push_back(42); input_vector.push_back(21); input_vector.push_back(-21); input_vector.push_back(-42);
		const int_vector v(input_vector.begin(), input_vector.end());
		int_vector::const_reverse_iterator it = v.rend() - 1;
		std::cout << "v.rend() = [" << *it << "]" << std::endl;
		// *it = -21;
	}
}

static void emptyTest() {
	printTitle("empty");
	int_vector v;
	printBool(v.empty());
	v.push_back(42);
	printBool(v.empty());
}

static void max_sizeTest() {

}

static void reserveTest() {

}

static void capacityTest() {

}

static void clearTest() {

}

static void insertTest() {

}

static void eraseTest() {

}

static void pop_backTest() {

}

static void resizeTest() {

}

static void swapTest() {

}

static void nonmember_operatorTest() {

}

static void nonmember_swapTest() {

}

void vectorTest() {
	constructorTest();
	assignTest();
	get_allocatorTest();

	// Element access
	atTest();
	operatorBracketTest();
	frontTest();
	backTest();
	dataTest();

	// Iterators
	iteratorsTest();

	// Capacity
	emptyTest();
	max_sizeTest();
	reserveTest();
	capacityTest();

	// Modifiers
	clearTest();
	insertTest();
	eraseTest();
	pop_backTest();
	resizeTest();
	swapTest();

	// Non-member functions
	nonmember_operatorTest();
	nonmember_swapTest();
}
