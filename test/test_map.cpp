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

static void assignTest() {
	printTitle("operator=");
	{
		int_map input_map;
		input_map.insert(ft::make_pair(42, "42"));
		input_map.insert(ft::make_pair(-42, "21"));
		printMap(input_map);
		int_map m;
		printMap(m);
		m = input_map;
		printMap(m);
	}
}

static void get_allocatorTest() {
	printTitle("get_allocator");
	std::allocator<ft::pair<const int, std::string> > alloc;
	int_map m;
	printBool(m.get_allocator() == alloc);
}


static void atTest() {
	printTitle("at");
	{
		printSubTitle("not const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		std::cout << "m.at(42) = [" << m.at(42) << "]" << std::endl;
		m.at(42) = "42tokyo";
		printMap(m);
		try {
			m.at(10000);
		} catch (std::out_of_range) {
			std::cout << "out_of_range" << '\n';
		}
	}
	{
		printSubTitle("not const");
		int_map input_map;
		input_map.insert(ft::make_pair(42, "42"));
		input_map.insert(ft::make_pair(-42, "21"));
		const int_map m(input_map);
		std::cout << "m.at(42) = [" << m.at(42) << "]" << std::endl;
		// m.at(42) = "42tokyo";
		printMap(m);
		try {
			m.at(10000);
		} catch (std::out_of_range) {
			std::cout << "out_of_range" << '\n';
		}
	}
}

static void operatorBracketTest() {
	printTitle("operator[]");
	{
		int_map input_map;
		input_map.insert(ft::make_pair(42, "42"));
		input_map.insert(ft::make_pair(-42, "-42"));
		int_map m(input_map);
		std::cout << "m[-42] = [" << m[-42] << "]" << std::endl;
		m[-42] = "42tokyo";
		printMap(m);
	}
}

static void iteratorsTest() {
	printTitle("iterators");
	{
		printSubTitle("begin not const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		int_map::iterator it = m.begin();
		std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		(*it).second = "new year";
		printMap(m);
	}
	{
		printSubTitle("begin const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		int_map::const_iterator it = m.begin();
		std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		// (*it).second = "new year";
		printMap(m);
	}
	{
		printSubTitle("end not const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		for (int_map::iterator it = m.begin(); it != m.end(); ++it) {
			std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
			std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		}
		int_map::iterator it = m.end();
		it--;
		(*it).second = "new year";
		printMap(m);
	}
	{
		printSubTitle("end const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		for (int_map::const_iterator it = m.begin(); it != m.end(); ++it) {
			std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
			std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		}
		int_map::const_iterator it = m.end();
		it--;
		// (*it).second = "new year";
		printMap(m);
	}
	{
		printSubTitle("rbegin not const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		int_map::reverse_iterator it = m.rbegin();
		std::cout << "m.rbegin().first = [" << (*it).first << "]" << std::endl;
		std::cout << "m.rbegin().second = [" << (*it).second << "]" << std::endl;
		(*it).second = "42paris";
		printMap(m);
	}
	{
		printSubTitle("rbegin const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		int_map::const_reverse_iterator it = m.rbegin();
		std::cout << "m.rbegin().first = [" << (*it).first << "]" << std::endl;
		std::cout << "m.rbegin().second = [" << (*it).second << "]" << std::endl;
		// (*it).second = "42paris";
		printMap(m);
	}
	{
		printSubTitle("rend not const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		for (int_map::reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
			std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
			std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		}
		int_map::reverse_iterator it = m.rend();
		it--;
		(*it).second = "new year";
		printMap(m);
	}
	{
		printSubTitle("rend const");
		int_map m;
		m.insert(ft::make_pair(42, "42"));
		m.insert(ft::make_pair(-42, "-42"));
		for (int_map::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it) {
			std::cout << "(*it).begin().first = [" << (*it).first << "]" << std::endl;
			std::cout << "(*it).begin().second = [" << (*it).second << "]" << std::endl;
		}
		int_map::const_reverse_iterator it = m.rend();
		it--;
		// (*it).second = "new year";
		printMap(m);
	}
}

static void emptyTest() {
	printTitle("empty");
	int_map m;
	printBool(m.empty());
	m.insert(ft::make_pair(42, "42"));
	printBool(m.empty());
}

static void sizeTest() {
	printTitle("size");
	int_map m;
	std::cout << "m.size() = [" << m.size() << "]" << std::endl;
	m.insert(ft::make_pair(42, "42"));
	std::cout << "m.size() = [" << m.size() << "]" << std::endl;
	m[1] = "one";
	m[2] = "two";
	m[3] = "three";
	m[4] = "four";
	std::cout << "m.size() = [" << m.size() << "]" << std::endl;
}

static void max_sizeTest() {
	// treeの構造が違うのでもちろん確保可能なサイズも変わる。
	// ここでは関数が呼び出されることを確認。
	printTitle("max_size");
	int_map m;
	m.max_size();
}

static void clearTest() {
	printTitle("clear");
	int_map m;
	m.insert(ft::make_pair(42, "42"));
	m.insert(ft::make_pair(-42, "-42"));
	printMap(m);
	m.clear();
	printMap(m);
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

static void swapTest() {
	printTitle("swap");
	{
		int_map m1;
		int_map m2;
		m1.insert(ft::make_pair(42, "42")); m1.insert(ft::make_pair(-42, "-42"));
		m2.insert(ft::make_pair(21, "m2!!"));
		m1.swap(m2);
		printMap(m1);
		printMap(m2);
	}
}

static void countTest() {
	printTitle("count");
	{
		int_map m;
		m.insert(ft::make_pair(42, "42")); m.insert(ft::make_pair(-42, "-42"));
		std::cout << "m.count() = [" << m.count(-42) << "]" << std::endl;
		std::cout << "m.count() = [" << m.count(INT_MIN) << "]" << std::endl;
		m.clear();
		std::cout << "m.count() = [" << m.count(42) << "]" << std::endl;
	}
}

static void findTest() {
	printTitle("find");
	{
		printSubTitle("not const");
		int_map m;
		m.insert(ft::make_pair(42, "42")); m.insert(ft::make_pair(-42, "-42"));
		int_map::iterator it = m.find(-42);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		(*it).second = "new year";
		printMap(m);
		it = m.find(INT_MAX);
		printBool(it == m.end());
	}
	{
		printSubTitle("const");
		int_map m;
		m.insert(ft::make_pair(42, "42")); m.insert(ft::make_pair(-42, "-42"));
		int_map::const_iterator it = m.find(-42);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		// (*it).second = "new year";
		it = m.find(INT_MAX);
		printBool(it == m.end());
	}
}

static void equal_rangeTest() {
	printTitle("equal_range");
	{
		printSubTitle("not const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		{
			ft::pair<int_map::iterator, int_map::iterator> p = m.equal_range(1);
			for (int_map::iterator& q = p.first; q != p.second; ++q)
				std::cout << "m[" << q ->first << "] = " << q->second << '\n';
	
			if (p.second == m.find(2))
				std::cout << "end of equal_range (p.second) is one-past p.first\n";
			else
				std::cout << "unexpected; p.second expected to be one-past p.first\n";
		}
		{
			ft::pair<int_map::iterator, int_map::iterator> pp = m.equal_range(-1);
			if (pp.first == m.begin())
				std::cout << "pp.first is iterator to first not-less than -1\n";
			else
				std::cout << "unexpected pp.first\n";
	
			if (pp.second == m.begin())
				std::cout << "pp.second is iterator to first element greater-than -1\n";
			else
				std::cout << "unexpected pp.second\n";
		}
		{
			ft::pair<int_map::iterator, int_map::iterator> ppp = m.equal_range(3);
			if (ppp.first == m.end())
				std::cout << "ppp.first is iterator to first not-less than 3\n";
			else
				std::cout << "unexpected ppp.first\n";
	
			if (ppp.second == m.end())
				std::cout << "ppp.second is iterator to first element greater-than 3\n";
			else
				std::cout << "unexpected ppp.second\n";
		}
		{
			// 代入
			ft::pair<int_map::iterator, int_map::iterator> p = m.equal_range(1);
			(*(p.first)).second = "42tokyo";
			printMap(m);
		}
	}
	{
		printSubTitle("const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		{
			ft::pair<int_map::const_iterator, int_map::const_iterator> p = m.equal_range(1);
			for (int_map::const_iterator& q = p.first; q != p.second; ++q)
				std::cout << "m[" << q ->first << "] = " << q->second << '\n';
	
			if (p.second == m.find(2))
				std::cout << "end of equal_range (p.second) is one-past p.first\n";
			else
				std::cout << "unexpected; p.second expected to be one-past p.first\n";
		}
		{
			ft::pair<int_map::const_iterator, int_map::const_iterator> pp = m.equal_range(-1);
			if (pp.first == m.begin())
				std::cout << "pp.first is iterator to first not-less than -1\n";
			else
				std::cout << "unexpected pp.first\n";
	
			if (pp.second == m.begin())
				std::cout << "pp.second is iterator to first element greater-than -1\n";
			else
				std::cout << "unexpected pp.second\n";
		}
		{
			ft::pair<int_map::const_iterator, int_map::const_iterator> ppp = m.equal_range(3);
			if (ppp.first == m.end())
				std::cout << "ppp.first is iterator to first not-less than 3\n";
			else
				std::cout << "unexpected ppp.first\n";
	
			if (ppp.second == m.end())
				std::cout << "ppp.second is iterator to first element greater-than 3\n";
			else
				std::cout << "unexpected ppp.second\n";
		}
		{
			// 代入
			// ft::pair<int_map::const_iterator, int_map::const_iterator> p = m.equal_range(1);
			// (*(p.first)).second = "42tokyo";
			// printMap(m);
		}
	}
}

static void lower_boundTest() {
	printTitle("lower_bound");
	{
		printSubTitle("not const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		int_map::iterator it = m.lower_bound(-1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		(*it).second = "ZEEEROO";
		printMap(m);

		it = m.lower_bound(1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;

		it = m.lower_bound(4);
		printBool(it == m.end());
	}
	{
		printSubTitle("const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		int_map::const_iterator it = m.lower_bound(-1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		// (*it).second = "ZEEEROO";

		it = m.lower_bound(1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;

		it = m.lower_bound(4);
		printBool(it == m.end());
	}
}

static void upper_boundTest() {
	printTitle("upper_bound");
	{
		printSubTitle("not const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		int_map::iterator it = m.upper_bound(-1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		(*it).second = "ZEEEROO";
		printMap(m);

		it = m.upper_bound(1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;

		it = m.upper_bound(4);
		printBool(it == m.end());
	}
	{
		printSubTitle("const");
		int_map m;
		m[0] = "zero"; m[1] = "one"; m[2] = "two";
		int_map::const_iterator it = m.upper_bound(-1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;
		// (*it).second = "ZEEEROO";

		it = m.upper_bound(1);
		std::cout << "(*it).first = [" << (*it).first << "]" << std::endl;
		std::cout << "(*it).second = [" << (*it).second << "]" << std::endl;

		it = m.upper_bound(4);
		printBool(it == m.end());
	}
}

struct ModCmp {
	bool operator()(const int lhs, const int rhs) const {
		return (lhs % 97) < (rhs % 97);
	}
};

static void key_compTest() {
	printTitle("key_comp");
	ft::map<int, char, ModCmp> m;
	m[1] = 'a'; m[2] = 'b'; m[3] = 'c'; m[4] = 'd'; m[5] = 'e';
	 
	struct ModCmp comp_func = m.key_comp();
 
	for (ft::map<int, char, ModCmp>::iterator it = m.begin(); it != m.end(); ++it) {
		bool before = comp_func((*it).first, 100);
		bool after = comp_func(100, (*it).first);

		std::cout << '(' << (*it).first << ',' << (*it).second;
		if (!before && !after)
			std::cout << ") equivalent to key 100\n";
		else if (before)
			std::cout << ") goes before key 100\n";
		else if (after)
			std::cout << ") goes after key 100\n";
	}
}

static void value_compTest() {
	printTitle("value_comp");
	ft::map<int, char, ModCmp> m;
	m[1] = 'a'; m[2] = 'b'; m[3] = 'c'; m[4] = 'd'; m[5] = 'e';
	 
	ft::map<int, char, ModCmp>::value_compare comp_func = m.value_comp();
	const ft::pair<int, char> val(100, 'a');

	for (ft::map<int, char, ModCmp>::iterator it = m.begin(); it != m.end(); ++it) {
		bool before = comp_func(*it, val);
		bool after = comp_func(val, *it);

		std::cout << '(' << (*it).first << ',' << (*it).second;
		if (!before && !after)
			std::cout << ") equivalent to key 100\n";
		else if (before)
			std::cout << ") goes before key 100\n";
		else if (after)
			std::cout << ") goes after key 100\n";
	}
}

static void nonmember_operatorTest() {
	
}

void mapTest() {
	constructorTest();
	// keyがなかった時にインサーとされる処理を書いていない
	assignTest();
	get_allocatorTest();

	// Element access
	atTest();
	operatorBracketTest();

	// Iterators
	iteratorsTest();

	// Capacity
	emptyTest();
	sizeTest();
	max_sizeTest();

	// Modifiers
	clearTest();
	insertTest();
	eraseTest();
	swapTest();
	
	// Lookup
	countTest();
	findTest();
	equal_rangeTest();
	lower_boundTest();
	upper_boundTest();

	// Observers
	key_compTest();
	value_compTest();

	// Non-member functions
	nonmember_operatorTest();


	// value_compareTest();
	// operator_equalTest();
	// all_eraseTest();
}
