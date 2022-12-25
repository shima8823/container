#include "tester.hpp"
#include <vector>

__attribute__((destructor))
static void d() {
	std::cout << "===== leaks =====" << std::endl;
	system("leaks -q container");
}

// (1)なのの数字はcppreferenceの関数番号に対応している

static void constructorTest() {
	printTitle("constructor");
	{
		printTitle("(1)");
		int_vector v;
		v.push_back(42);
		printVector(v);
	}
	{
		printTitle("(2)");
		std::allocator<int> alloc;
		int_vector v(alloc);
		v.push_back(42);
		printVector(v);
	}
	{
		printTitle("(3)");
		std::allocator<int> alloc;
		int_vector v(20, 42, alloc);
		printVector(v);
	}
	{
		printTitle("(5)");
		std::allocator<int> alloc;
		int_vector inputVector(40, 21);
		int_vector v(inputVector.begin(), inputVector.end());
		int_vector v_alloc(inputVector.begin(), inputVector.end(), alloc);
		printVector(v);
		printVector(v_alloc);
	}
	{
		printTitle("(6)");
		int_vector inputVector(40, 21);
		int_vector v(inputVector);
		printVector(v);
	}

}


static void assignTest() {

}

static void atTest() {

}

static void operator_daikakkoTest() {

}

static void frontTest() {

}

static void backTest() {

}

static void dataTest() {

}

static void beginTest() {

}

static void rbeginTest() {

}

static void emptyTest() {

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
	atTest();
	operator_daikakkoTest();
	frontTest();
	backTest();
	dataTest();
	beginTest();
	rbeginTest();
	emptyTest();
	max_sizeTest();
	reserveTest();
	capacityTest();
	clearTest();
	insertTest();
	eraseTest();
	pop_backTest();
	resizeTest();
	swapTest();
	nonmember_operatorTest();
	nonmember_swapTest();
}
