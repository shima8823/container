#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

template<class _T1, class _T2>
struct pair {
	typedef _T1 first_type;
	typedef _T2 second_type;

	_T1 first;
	_T2 second;

	// constructor

	pair() : first(), second() {}
	pair( const _T1& x, const _T2& y ) : first(x), second(y) {}
	template< class _U1, class _U2 >
	pair( const pair<_U1, _U2>& p ) : first(p.first), second(p.second) {}

	// operator=

	pair& operator=( const pair& other ) {
		if (this == &other) return *this;
		first = other.first;
		second = other.second;
		return *this;
	}
};

// Non-member functions

template< class _T1, class _T2 >
ft::pair<_T1, _T2> make_pair( _T1 t, _T2 u ) {
	return pair<_T1, _T2>(t, u);
}

template< class T1, class T2 >
bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template< class T1, class T2 >
bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	!(lhs == rhs);
}

template< class T1, class T2 >
bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template< class T1, class T2 >
bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return !(rhs < lhs);
}

template< class T1, class T2 >
bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	return rhs < lhs;
}

template< class T1, class T2 >
bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) {
	!(lhs < rhs);
}

} // namespace ft

#endif
