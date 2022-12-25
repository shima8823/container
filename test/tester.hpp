#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>

#define MAGENTA	"\033[35m"
#define WHITE	"\033[37m"

#if ISSTL
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif

typedef ft::vector<int> int_vector;

// utils.cpp
void printTitle(std::string s);
void printSubTitle(std::string s);
void printBool(bool b);


template<class T>
void printVector(T& v) {
	std::cout << "size:" << v.size() << " capacity:" << v.capacity() << std::endl;
	std::cout << "{ ";
	for (typename T::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;
}

// const
template<class T>
void printVector(const T& v) {
	std::cout << "size:" << v.size() << " capacity:" << v.capacity() << std::endl;
	std::cout << "{ ";
	for (typename T::const_iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << " ";
	std::cout << "}" << std::endl;
}

// test_vector.cpp
void vectorTest();

#endif
