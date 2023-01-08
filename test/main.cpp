#include "tester.hpp"

int main() {
	printContainerTitle("vector");
	vectorTest();
	printContainerTitle("map");
	mapTest();
	printContainerTitle("stack");
	stackTest();
}
