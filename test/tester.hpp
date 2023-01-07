#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>

#define MAGENTA	"\033[35m"
#define WHITE	"\033[37m"
#define CYAN	"\033[36m"
#define GREEN	"\033[32m"

#if ISSTL
	#include <vector>
	#include <map>
	#include <stack>
	namespace ft = std;
#else
	#include <vector.hpp>
	#include <map.hpp>
	#include <stack.hpp>
#endif

typedef ft::vector<int> int_vector;

// utils.cpp
void printContainerTitle(std::string s);
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

template <typename T, typename U>
void printMap(const ft::map<T, U> & m) {
	std::cout << "size:" << m.size() << std::endl;
	std::cout << "{ ";
	for (typename ft::map<T, U>::const_iterator it = m.begin(); it != m.end(); ++it)
		std::cout << CYAN << "[" << it->first << "]" << WHITE << ": " << it->second << " ";
	std::cout << "}" << std::endl;
}

// test_vector.cpp
void vectorTest();

// test_map.cpp
void mapTest();

// test_stack.cpp
void stackTest();

#endif
