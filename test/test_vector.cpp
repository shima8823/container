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
		} catch (std::out_of_range) {
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
		} catch (std::out_of_range) {
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

static void sizeTest() {
	printTitle("size");
	int_vector v;
	std::cout << "v.size() = [" << v.size() << "]" << std::endl;
	v.push_back(10);
	std::cout << "v.size() = [" << v.size() << "]" << std::endl;
	v.push_back(10);
	v.push_back(10);
	v.push_back(10);
	std::cout << "v.size() = [" << v.size() << "]" << std::endl;
}

static void max_sizeTest() {
	printTitle("max_size");
	int_vector v;
	std::cout << "v.max_size() = [" << v.max_size() << "]" << std::endl;
}

static void reserveAndCapacityTest() {
	printTitle("reserve and capacity");
	int_vector v;
	printVector(v);
	v.push_back(10);
	v.reserve(0);
	printVector(v);
	v.reserve(10000);
	printVector(v);
}

static void clearTest() {
	printTitle("clear");
	int_vector v;
	v.push_back(10);
	printVector(v);
	v.clear();
	printVector(v);
	v.push_back(42); v.push_back(42); v.push_back(42);
	v.reserve(10000);
	printVector(v);
	v.clear();
	printVector(v);
}

static void insertTest() {
	printTitle("insert");
	{
		printSubTitle("(1)");
		int_vector v;
		printVector(v);
		int_vector::iterator it = v.insert(v.begin(), 10);
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);

		it = v.insert(v.end() - 1, 42);
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);
	}
	{
		printSubTitle("(3)");
		int_vector v;
		printVector(v);
		v.insert(v.begin(), 0, 42);
		printVector(v);

		try {
			v.insert(v.begin(), v.max_size() + 1, 42);
		} catch (std::length_error) {
			std::cout << "size too big" << std::endl;
		}

		v.insert(v.begin(), 5, 42);
		printVector(v);
		v.insert(v.begin() + 1, 1, 21);
		printVector(v);

		v.reserve(100);
		printVector(v);
		v.insert(v.end(), 3, -21);
		printVector(v);
	}
	{
		printSubTitle("(4)");
		int_vector input_vector;
		input_vector.push_back(42);input_vector.push_back(21);input_vector.push_back(-21);input_vector.push_back(-42);
		int_vector v;
		v.insert(v.begin(), input_vector.begin(), input_vector.end());
		printVector(v);
		v.insert(v.end() - 1, input_vector.begin(), input_vector.end());
		printVector(v);
	}
}

static void eraseTest() {
	printTitle("erase");
	{
		printSubTitle("(1)");
		int_vector v;
		v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-42);
		int_vector::iterator it = v.erase(v.begin() + 2);
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);
	}
	{
		printSubTitle("(2)");
		int_vector v;
		v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-42);

		int_vector::iterator it = v.erase(v.begin(), v.begin());
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);

		it = v.erase(v.begin() + 2, v.end() - 1);
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);

		it = v.erase(v.begin(), v.end());
		std::cout << "*it = [" << *it << "]" << std::endl;
		printVector(v);
	}
}

static void pop_push_backTest() {
	printTitle("pop_push_back");
	{
		printSubTitle("push_back");
		int_vector v;
		v.push_back(42);
		printVector(v);
		v.push_back(21); v.push_back(-21); v.push_back(-42); v.push_back(8);
		printVector(v);
	}
	{
		printSubTitle("pop_back");
		int_vector v;
		v.push_back(42);
		printVector(v);
		v.pop_back();
		printVector(v);
		v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-42);
		printVector(v);
		v.pop_back();
		printVector(v);
	}
}

static void resizeTest() {
	printTitle("pop_push_back");
	{
		int_vector v;
		v.push_back(42);v.push_back(21); v.push_back(-21); v.push_back(-42);
		v.resize(2);
		printVector(v);

		v.resize(5, 100);
		printVector(v);
	}
}

static void swapTest() {
	printTitle("swap");
	{
		int_vector v;
		int_vector v2;
		v.push_back(42);v.push_back(21); v.push_back(-21); v.push_back(-42);
		printVector(v);

		v.swap(v2);
		printVector(v);
		printVector(v2);
	}
}

static void nonmember_operatorTest() {
	printTitle("nonmember_operator");
	{
		printSubTitle("==");
		int_vector v;
		int_vector v2;
		v.push_back(42);v.push_back(21); v.push_back(-21); v.push_back(-42);
		v2.push_back(42);v2.push_back(21); v2.push_back(-21); v2.push_back(-42);
		printBool(v == v2);
		v2.reserve(10);
		printBool(v == v2); // capacity
		v2.push_back(42);
		printBool(v == v2); // size !=
		v2.pop_back(); v2.pop_back(); v2.push_back(42);
		printVector(v2);
		printBool(v == v2); // value !=
	}
	{
		printSubTitle("!=");
		int_vector v;
		int_vector v2;
		v.push_back(42);v.push_back(21); v.push_back(-21); v.push_back(-42);
		v2.push_back(42);v2.push_back(21); v2.push_back(-21); v2.push_back(-42);
		printBool(v != v2);
		v2.reserve(10);
		printBool(v != v2); // capacity
		v2.push_back(42);
		printBool(v != v2); // size !=
		v2.pop_back(); v2.pop_back(); v2.push_back(42);
		printVector(v2);
		printBool(v != v2); // value !=
	}
	{
		printSubTitle("<");
		int_vector v;
		int_vector v2;
		v.push_back(0);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v < v2); // 0 < 42
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(0);v2.push_back(21);
		printBool(v < v2); // 42 < 0
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);v2.push_back(-21);
		printBool(v < v2); // first1 == last1 && first2 != last2;
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);v.push_back(-21);
		v2.push_back(42);v2.push_back(21);
		printBool(v < v2); // first1 != last1
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v < v2); // first2 == last2;
		v.clear();
		v2.clear();
	}
	{
		printSubTitle("<=");
		int_vector v;
		int_vector v2;
		v.push_back(0);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v <= v2); // 0 < 42
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(0);v2.push_back(21);
		printBool(v <= v2); // 42 < 0
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);v2.push_back(-21);
		printBool(v <= v2); // first1 == last1 && first2 != last2;
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);v.push_back(-21);
		v2.push_back(42);v2.push_back(21);
		printBool(v <= v2); // first1 != last1
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v <= v2); // first2 == last2;
		v.clear();
		v2.clear();
	}
	{
		printSubTitle(">");
		int_vector v;
		int_vector v2;
		v.push_back(0);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v > v2); // 0 < 42
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(0);v2.push_back(21);
		printBool(v > v2); // 42 < 0
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);v2.push_back(-21);
		printBool(v > v2); // first1 == last1 && first2 != last2;
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);v.push_back(-21);
		v2.push_back(42);v2.push_back(21);
		printBool(v > v2); // first1 != last1
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v > v2); // first2 == last2;
		v.clear();
		v2.clear();
	}
	{
		printSubTitle(">=");
		int_vector v;
		int_vector v2;
		v.push_back(0);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v >= v2); // 0 < 42
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(0);v2.push_back(21);
		printBool(v >= v2); // 42 < 0
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);v2.push_back(-21);
		printBool(v >= v2); // first1 == last1 && first2 != last2;
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);v.push_back(-21);
		v2.push_back(42);v2.push_back(21);
		printBool(v >= v2); // first1 != last1
		v.clear();
		v2.clear();

		v.push_back(42);v.push_back(21);
		v2.push_back(42);v2.push_back(21);
		printBool(v >= v2); // first2 == last2;
		v.clear();
		v2.clear();
	}
}

static void nonmember_swapTest() {
	printTitle("nonmember_swap");
	int_vector v;
	v.push_back(42); v.push_back(21); v.push_back(-21); v.push_back(-42);
	int_vector v2;

	printVector(v);
	printVector(v2);
	std::swap(v, v2);
	printVector(v);
	printVector(v2);
}

static bool compare(int a, int b) {
	return a > b;
}

static void algorithmTest() {
	// コンパイルできるかどうかだけ
	printTitle("algorithm");
	{
		printSubTitle("equal");
		int_vector v;
		int_vector v2;
		v.push_back(42);
		v2.push_back(21);

		ft::equal(v.begin(), v.end(), v2.begin(), compare);
	}
	{
		printSubTitle("lexicographical_compare");
		int_vector v;
		int_vector v2;
		v.push_back(42);
		v2.push_back(21);

		ft::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end(), compare);
	}
	
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
	sizeTest();
	max_sizeTest();
	reserveAndCapacityTest();

	// Modifiers
	clearTest();
	insertTest();
	eraseTest();
	pop_push_backTest();
	resizeTest();
	swapTest();

	// Non-member functions
	nonmember_operatorTest();
	nonmember_swapTest();

	// algorithm
	algorithmTest();
}
