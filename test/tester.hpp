#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <vector.hpp>

typedef ft::vector<int> int_vector;

// utils.cpp
void printTitle(std::string& s);

template<class T>
void printVector(T& v) {
	std::cout << "size:" << v.size() << " capacity:" << v.capacity() << std::endl;
	std::cout << "{ ";
	for (typename T::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;
}

// test_vector.cpp
void vectorTest();

#endif
