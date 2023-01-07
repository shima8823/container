#include "tester.hpp"

typedef ft::map<int, std::string> int_map;

// printSubTitleの(1)などの数字はcppreferenceの関数番号に対応している
// ● = red ○ = black

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
		try {
			m.at(0);
		} catch (std::out_of_range) {
			std::cout << "out_of_range" << '\n';
		}
		try {
			m.at(INT_MAX);
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
		try {
			m.at(0);
		} catch (std::out_of_range) {
			std::cout << "out_of_range" << '\n';
		}
		try {
			m.at(INT_MAX);
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
	{
		int_map m;
		m[-42] = "-42";
		m[42] = "42tokyo";
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
		printSubTitle("(1)");

		ft::pair<int_map::iterator, bool> res;
		int_map m;
		res = m.insert(ft::make_pair(10, "hello"));
		printMap(m);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		/*
				○
		*/
		res = m.insert(ft::make_pair(2, "bye"));
		printMap(m);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		/*
				○
			●
		*/
		res = m.insert(ft::make_pair(4, "bye"));
		printMap(m);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		/* 叔父が黒 + new_nodeが親の右の子
				○		   4
			●		→	
				4		  ●	●
		*/
		res = m.insert(ft::make_pair(15, "bye"));
		printMap(m);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		/*	叔父ノードが赤色
				○			    	○
			●		●	->	   ○		○
						15						15
		*/
		int_map m2;
		m2[20] = "twenty"; m2[10] = "ten";
		res = m2.insert(ft::make_pair(5, "five"));
		printMap(m2);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		/*	叔父が黒 + new_nodeが親の左の子
					○			    ○
				●		->	   5		●
			5						
		*/
		res = m2.insert(ft::make_pair(13, "five"));
		printMap(m2);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		// --j
	
		res = m2.insert(ft::make_pair(20, "bye"));
		printMap(m2);
		std::cout << "(*res.first).first = [" << (*res.first).first << "]" << std::endl;
		std::cout << "(*res.first).first = [" << (*res.first).second << "]" << std::endl;
		printBool(res.second);
		// falseの時
	}
	{
		printSubTitle("(4)");

		int_map::iterator res;
		int_map m;
		res = m.insert(m.end(), ft::make_pair(0, "zero"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;

		m[2] = "two"; m[40] = "fourty one";
		int_map::iterator it = m.begin();
		it++;
		res = m.insert(it, ft::make_pair(42, "fourty two"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;

		// _Res(__after._M_node, __after._M_node);
		res = m.insert(it, ft::make_pair(3, "three"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;
	
		// _Res(0, __pos._M_node);
		res = m.insert(++it, ft::make_pair(10, "ten"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;

		res = m.insert(m.end(), ft::make_pair(100, "one hun"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;

		// _Res(__pos._M_node, __pos._M_node);
		res = m.insert(--(m.end()), ft::make_pair(70, "seventy"));
		printMap(m);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;

		int_map m2;
		res = m2.insert(m2.begin(), ft::make_pair(100, "^-^"));
		res = m2.insert(m2.begin(), ft::make_pair(50, "^-^"));
		res = m2.insert(m2.begin(), ft::make_pair(25, "^-^"));
		res = m2.insert(m2.begin(), ft::make_pair(150, "^-^"));
		res = m2.insert(m2.begin(), ft::make_pair(37, "^-^"));
		res = m2.insert(m2.begin(), ft::make_pair(13, "^-^"));
		// _Res(0, __before._M_node);
		res = m2.insert((++(++(++(m2.begin())))), ft::make_pair(40, "^-^"));
		printMap(m2);
		std::cout << "(*res).first = [" << (*res).first << "]" << std::endl;
		std::cout << "(*res).second = [" << (*res).second << "]" << std::endl;
	}
	{
		printSubTitle("(7)");

		int_map input_map;
		input_map[-10] = "negative ten"; input_map[3] = "three"; input_map[104] = "one hundred four";
		int_map m;
		m[0] = "zero"; m[2] = "two"; m[4] = "four";
		m.insert(input_map.begin(), input_map.end());
		printMap(m);
	}
}

static void eraseTest() {
	printTitle("erase");
	{
		printSubTitle("(1)");

		int_map m;
		int_map::iterator it;
		
		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four";
		printMap(m);
		it = m.begin();
		m.erase(it);  // it == m[0]
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four";
		printMap(m);
		it = m.find(4);
		m.erase(it);  // it == m[4]
		printMap(m);

		m.clear();
		m[2] = "two";
		printMap(m);
		it = m.find(2);
		m.erase(it);  // it == m[2]
		printMap(m);

		m.clear();
		m[2] = "two";m[0] = "zero";
		printMap(m);
		it = m.find(2);
		m.erase(it);  // it == m[2]
		printMap(m);

		m.clear();
		m[2] = "two";m[3] = "three";
		printMap(m);
		it = m.find(2);
		m.erase(it);  // it == m[2]
		printMap(m);

		// 削除するノードの子が2個
		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four";
		printMap(m);
		it = m.find(2);
		m.erase(it); // it == m[2]
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[3] = "three";
		printMap(m);
		it = m.find(2);
		m.erase(it); // it == m[2]
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[10] = "ten"; m[3] = "three";
		printMap(m);
		it = m.find(2);
		m.erase(it); // it == m[2]
		printMap(m);

		m.clear();
		m[500] = "";m[250] = "";m[750] = ""; m[125] = "";m[625] = "";m[375] = "";m[1000] = "";
		printMap(m);
		it = m.find(250);
		m.erase(it); // it == m[250]
		printMap(m);

		m.clear();
		m[500] = "";m[250] = "";m[750] = ""; m[125] = "";m[625] = "";m[375] = "";m[1000] = "";m[1200] = "";m[690] = "";
		printMap(m);
		it = m.find(500);
		m.erase(it); // it == m[500]
		printMap(m);

		m.clear();
		m[500] = "";m[250] = "";m[750] = ""; m[125] = "";m[625] = "";m[375] = "";m[1000] = "";m[1200] = "";
		printMap(m);
		it = m.find(625);
		m.erase(it); // it == m[625]
		printMap(m);

		m.clear();
		m[500] = "";m[250] = "";m[750] = ""; m[125] = "";m[625] = "";m[375] = "";m[1000] = "";m[1200] = "";
		m.erase(m.find(1200));m.erase(m.find(125));m.erase(m.find(375));
		printMap(m);
		m.erase(m.find(250));
		printMap(m);

		m.clear(); // 目で確認
		m[500] = "";m[250] = "";m[750] = ""; m[125] = "";m[625] = "";m[375] = "";m[1000] = "";m[800] = "";
		printMap(m);
		it = m.find(625);
		m.erase(it); // it == m[625]
		printMap(m);
	}
	{
		printSubTitle("(2)");
		int_map m;

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[6] = "six";
		printMap(m);
		m.erase(m.find(2), m.end());
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[6] = "six";
		printMap(m);
		m.erase(m.begin(), m.end());
		printMap(m);
	}
	{
		printSubTitle("(3)");
		int_map m;

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[6] = "six";
		printMap(m);
		m.erase(2);
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[6] = "six";m[5] = "five";
		printMap(m);
		m.erase(4);
		printMap(m);

		m.clear();
		m[0] = "zero"; m[2] = "two"; m[4] = "four"; m[6] = "six";m[9] = "nine";
		printMap(m);
		m.erase(7);
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
		printMap(m1);
		printMap(m2);
		m1.swap(m2);
		printMap(m1);	
		printMap(m2);

		m1.clear(); m2.clear();
		m1.swap(m2);
		printMap(m1);
		printMap(m2);

		m1.clear(); m2.clear();
		m1[10] = "ten";
		printMap(m1);
		printMap(m2);
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
		it = m.find(0);
		printBool(it == m.end());
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
		it = m.find(0);
		printBool(it == m.end());
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
	printTitle("nonmember_operator");
	ft::map<int, char> alice;
	alice[1] = 'a'; alice[2] = 'b'; alice[3] = 'c';
	ft::map<int, char> bob;
	bob[7] = 'Z'; bob[8] = 'Y'; bob[9] = 'X'; bob[10] = 'W';
	ft::map<int, char> eve;
	eve[1] = 'a'; eve[2] = 'b'; eve[3] = 'c';

	std::cout << std::boolalpha;

	// Compare non equal containers
	std::cout << "alice == bob returns "; printBool(alice == bob);
	std::cout << "alice != bob returns "; printBool(alice != bob);
	std::cout << "alice <  bob returns "; printBool(alice < bob);
	std::cout << "alice <= bob returns "; printBool(alice <= bob);
	std::cout << "alice >  bob returns "; printBool(alice > bob);
	std::cout << "alice >= bob returns "; printBool(alice >= bob);

	std::cout << '\n';

	// Compare equal containers
	std::cout << "alice == eve returns "; printBool(alice == eve);
	std::cout << "alice != eve returns "; printBool(alice != eve);
	std::cout << "alice <  eve returns "; printBool(alice < eve);
	std::cout << "alice <= eve returns "; printBool(alice <= eve);
	std::cout << "alice >  eve returns "; printBool(alice > eve);
	std::cout << "alice >= eve returns "; printBool(alice >= eve);
}

static void nonmember_swapTest() {
	printTitle("nonmember_swap");
	{
		int_map m1;
		int_map m2;
		m1.insert(ft::make_pair(42, "42")); m1.insert(ft::make_pair(-42, "-42"));
		m2.insert(ft::make_pair(21, "m2!!"));
		printMap(m1);
		printMap(m2);
		std::swap(m1, m2);
		printMap(m1);
		printMap(m2);
	}
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
	nonmember_swapTest();
}
