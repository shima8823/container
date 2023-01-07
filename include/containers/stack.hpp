#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{

public:
	typedef Container							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference		reference;
	typedef typename Container::const_reference	const_reference;

	explicit stack( const Container& cont = Container() ) : c(cont) {}

	stack( const stack& other ) : c(other.c) {}

	~stack() {}

	stack& operator=( const stack& other ) {c = other.c; return *this;}

	// Element access

	reference top() {return c.back();}
	const_reference top() const {return c.back();}

	// Capacity
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}

	// Modifiers
	void push( const value_type& value ) {c.push_back(value);}
	void pop() {c.pop_back();}

	// friendは非公開メンバのContainer cを使用するため。
	template< class T1, class C1 >
	friend bool operator==( const ft::stack<T1,C1>& lhs, const ft::stack<T1,C1>& rhs );
	template< class T1, class C1 >
	friend bool operator<( const ft::stack<T1,C1>& lhs, const ft::stack<T1,C1>& rhs );

protected:
	// Member objects
	Container c;

};

template< class T, class Container >
bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return lhs.c == rhs.c;
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return lhs.c < rhs.c;
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return !(rhs < lhs);
}

template< class T, class Container >
bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return rhs < lhs;
}

template< class T, class Container >
bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
{
	return !(lhs < rhs);
}

} // namespace ft

#endif
