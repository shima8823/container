#include "tester.hpp"

void printTitle(std::string s) {
	std::cout << std::endl
			  << MAGENTA
			  << "------"
			  << s
			  << "------"
			  << WHITE
			  << std::endl;
}

void printSubTitle(std::string s) {
	std::cout << std::endl
			  << "------"
			  << s
			  << "------"
			  << std::endl;
}

void printBool(bool b) {
	std::cout << (b ? "true" : "false") << std::endl;
}
