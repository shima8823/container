#include "tester.hpp"

typedef ft::map<int, std::string> int_map;

// printSubTitleの(1)などの数字はcppreferenceの関数番号に対応している

static void constructorTest() {
	printTitle("constructor");
	{
		printSubTitle("(1)");
		int_map m;
		printMap(m);
	}
	{
		printSubTitle("(2)");
		std::allocator<ft::pair<const int, std::string> > alloc;
		std::less<int> comp;
		int_map m(comp, alloc);
		printMap(m);
	}
	{
		printSubTitle("(4)");
		int_map input_map;
		input_map.insert(ft::make_pair(-42, "42"));
		input_map.insert(ft::make_pair(42, "42"));
		int_map m(input_map.begin(), input_map.end());
		printMap(m);
	}
	{
		printSubTitle("(6)");
		int_map input_map;
		input_map.insert(ft::make_pair(-42, "tokyo"));
		input_map.insert(ft::make_pair(42, "paris"));
		printMap(input_map);
		int_map m(input_map);
		printMap(m);
	}
}

static void get_allocatorTest() {
	
}

static void insertTest() {
	printTitle("insert");
	{
		int_map m;
		
		m.insert(ft::make_pair(10, "hello"));
		printMap(m);
		m.insert(ft::make_pair(-2, "bye"));
		printMap(m);
	}
}

static void eraseTest() {
	printTitle("erase");
	{
		int_map m;
		
		m.insert(ft::make_pair(10, "hello"));
		printMap(m);
		m.insert(ft::make_pair(-2, "bye"));
		printMap(m);
		m.erase(-2);
		printMap(m);
	}
}


void mapTest() {
	constructorTest();
	get_allocatorTest();
	insertTest();
	eraseTest();
	// value_compareTest();
	// operator_equalTest();
	// all_eraseTest();
	// get_allocTest();
	// atTest();
	// insert_iteratorTest();
	// insert_iterator_iteratorTest();
	// operator_kakkoTest();
	// beginTest();
	// rbeginTest();
	// emptyTest();
	// max_sizeTest();
	// clearTest();
	// swapTest();
	// findTest();
	// equal_rangeTest();
	// copy_constructTest();
	// lower_boundTest();
	// key_compTest();
	// value_compTest();
	// non_member_operatorTest();
}
