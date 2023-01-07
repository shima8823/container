#include "tester.hpp"
#include <list>

static void printStack(ft::stack<int> s) {
	std::cout << "size:" << s.size() << std::endl;
	std::cout << "{ ";
	int tmp;
	while (!s.empty()) {
		tmp = s.top();
		std::cout << tmp << " ";
		s.pop();
	}
	std::cout << "}" << std::endl;
}

static void constructorTest() {
	printTitle("constructor");
	{
		ft::stack<int> s;
		printStack(s);
	}
	{
		ft::stack<int, std::list<int> > s;
	}
	{
		printSubTitle("copy constructor");
		ft::stack<int> input_stack;
		input_stack.push(10);
		input_stack.push(20);
		input_stack.push(30);
		input_stack.push(0);
		printStack(input_stack);

		ft::stack<int> s(input_stack);
		printStack(s);
	}
}

static void assignTest() {
	printTitle("assign");
	{
		ft::stack<int> input_stack;
		input_stack.push(10);
		input_stack.push(20);
		input_stack.push(30);
		input_stack.push(0);
		printStack(input_stack);

		ft::stack<int> s;
		s = input_stack;
		printStack(s);
	}
}

static void topTest() {
	printTitle("top");
	{
		printSubTitle("not const");
		{
			ft::stack<int> s;
			s.push(10); s.push(20); s.push(30); s.push(0);
			printStack(s);
			std::cout << "s.top() = [" << s.top() << "]" << std::endl;
			s.top() = 42;
			printStack(s);
		}
		printSubTitle("const");
		{
			ft::stack<int> input_stack;
			input_stack.push(10); input_stack.push(20); input_stack.push(30); input_stack.push(0);

			const ft::stack<int> s(input_stack);
			printStack(s);
			std::cout << "s.top() = [" << s.top() << "]" << std::endl;
			// s.top() = 42;
			printStack(s);
		}
	}
}

static void emptyTest() {
	printTitle("empty");
	{
		ft::stack<int> s;
		printBool(s.empty());
		s.push(42);
		printBool(s.empty());
	}
}

static void sizeTest() {
	printTitle("size");
	{
		ft::stack<int> s;
		std::cout << "s.size() = [" << s.size() << "]" << std::endl;
		s.push(42);
		std::cout << "s.size() = [" << s.size() << "]" << std::endl;
		for (int i = 0; i < 5; i++)
			s.push(i);
		std::cout << "s.size() = [" << s.size() << "]" << std::endl;
	}
}

static void pushTest() {
	printTitle("push");
	{
		ft::stack<int> s;
		s.push(10); s.push(20); s.push(30); s.push(0);
		printStack(s);
		s.push(10); s.push(20); s.push(30); s.push(0);
		printStack(s);
	}
}

static void popTest() {
	printTitle("pop");
	{
		ft::stack<int> s;
		s.push(10); s.push(20); s.push(30); s.push(0);
		printStack(s);
		s.pop();
		printStack(s);
		s.pop();s.pop();s.pop();
		printStack(s);
	}
}

static void nonmemberOperatorTest() {
	printTitle("nonmemberOperator");
	{
		ft::stack<int> alice;	alice.push(1);alice.push(2);alice.push(3);
		ft::stack<int> bob;		bob.push(7);bob.push(8);bob.push(9);bob.push(10);
		ft::stack<int> eve;		eve.push(1);eve.push(2);eve.push(3);
	
		std::cout << "alice == bob returns "; printBool(alice == bob);
		std::cout << "alice != bob returns "; printBool(alice != bob);
		std::cout << "alice <  bob returns "; printBool(alice < bob);
		std::cout << "alice <= bob returns "; printBool(alice <= bob);
		std::cout << "alice >  bob returns "; printBool(alice > bob);
		std::cout << "alice >= bob returns "; printBool(alice >= bob);
	
		std::cout << '\n';
	
		std::cout << "alice == eve returns "; printBool(alice == eve);
		std::cout << "alice != eve returns "; printBool(alice != eve);
		std::cout << "alice <  eve returns "; printBool(alice < eve);
		std::cout << "alice <= eve returns "; printBool(alice <= eve);
		std::cout << "alice >  eve returns "; printBool(alice > eve);
		std::cout << "alice >= eve returns "; printBool(alice >= eve);
	}
}


void stackTest() {
	constructorTest();
	assignTest();

	// Element access
	topTest();

	// Capacity
	emptyTest();
	sizeTest();

	// Modifiers
	pushTest();
	popTest();

	// Non-member functions
	nonmemberOperatorTest();
}
