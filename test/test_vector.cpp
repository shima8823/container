#include "tester.hpp"
#include <vector>

static void constructTest() {
	int_vector v;
	// std::vector<int> v;
	v.push_back(19);
	printVector(v);
}

static void copy_constructTest() {

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
	constructTest();
	copy_constructTest();
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