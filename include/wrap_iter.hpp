#ifndef WRAP_ITER_HPP
#define WRAP_ITER_HPP

namespace ft
{

template <class Iter>
class wrap_iter
{
protected:
	Iter _current;
	typedef ft::iterator_traits<Iter> traits_type;

public:
	typedef Iter	iterator_type;
	typedef typename traits_type::iterator_category	iterator_category;
	typedef typename traits_type::value_type		value_type;
	typedef typename traits_type::difference_type	difference_type;
	typedef typename traits_type::pointer			pointer;
	typedef typename traits_type::reference			reference;

	// member functions
	wrap_iter() : _current(NULL) {}
	explicit wrap_iter(iterator_type x) : _current(x) {}
	template< class U >
	wrap_iter(const wrap_iter<U>& other) : _current(other.base()) {}

	template< class U >
	wrap_iter& operator=(const ft::wrap_iter<U>& other) {
		if (this == &other)
			return *this;
		_current = other.base();
		return *this;
	}

	~wrap_iter() {}

	iterator_type base() const { return _current };
	reference operator*() const { return *_current;}
	pointer operator->() const { return _current; };

	reference operator[](difference_type n) const { return *(*this + n)};

	wrap_iter& operator++() {++_current; return *this;}
	wrap_iter& operator--() {--_current; return *this;}
	wrap_iter operator++( int ) {wrap_iter __tmp = *this; ++_current; return __tmp;}
	wrap_iter operator--( int ) {wrap_iter __tmp = *this; --_current; return __tmp;}
	wrap_iter operator+( difference_type n ) const {return wrap_iter(_current + n);}
	wrap_iter operator-( difference_type n ) const {return wrap_iter(_current - n);}
	wrap_iter& operator+=( difference_type n ) {_current += n; return *this;}
	wrap_iter& operator-=( difference_type n ) {_current -= n; return *this;}

	// non member functions
	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::wrap_iter<Iterator1>& lhs,
					const ft::wrap_iter<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iter >
	ft::wrap_iter<Iter>
	operator+( typename ft::wrap_iter<Iter>::difference_type n,
				const ft::wrap_iter<Iter>& it )
	{
		it += n;
		return it;
	}

	template< class Iterator >
	typename ft::wrap_iter<Iterator>::difference_type
	operator-( const ft::wrap_iter<Iterator>& lhs,
				const ft::wrap_iter<Iterator>& rhs )
	{
		return lhs.base() - rhs.base();
	}
};

} // namespace ft


#endif
