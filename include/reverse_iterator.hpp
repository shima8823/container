#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft
{

template <class Iter>
class reverse_iterator : public
	iterator<typename ft::iterator_traits<Iter>::iterator_category,
				typename ft::iterator_traits<Iter>::value_type,
				typename ft::iterator_traits<Iter>::difference_type,
				typename ft::iterator_traits<Iter>::pointer,
				typename ft::iterator_traits<Iter>::reference>
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
	reverse_iterator() : _current() {}
	explicit reverse_iterator(iterator_type x) : _current(x) {}
	template< class U >
	reverse_iterator(const reverse_iterator<U>& other) : _current(other.base()) {}

	template< class U >
	reverse_iterator& operator=(const ft::reverse_iterator<U>& other) {
		_current = other.base();
		return *this;
	}

	virtual ~reverse_iterator() {} // ?

	iterator_type base() const { return _current };
	reference operator*() const {Iter tmp = _current; return *--tmp;}
	pointer operator->() const { return &(operator*()); };

	reference operator[](difference_type n) const { return *(*this + n)};

	reverse_iterator& operator++() {--_current; return *this;}
	reverse_iterator& operator--() {++_current; return *this;}
	reverse_iterator operator++( int ) {reverse_iterator __tmp = *this; --_current; return __tmp;}
	reverse_iterator operator--( int ) {reverse_iterator __tmp = *this; ++_current; return __tmp;}
	reverse_iterator operator+( difference_type n ) const {return reverse_iterator(_current - n);}
	reverse_iterator operator-( difference_type n ) const {return reverse_iterator(_current + n);}
	reverse_iterator& operator+=( difference_type n ) {_current -= n; return *this;}
	reverse_iterator& operator-=( difference_type n ) {_current += n; return *this;}

	// non member functions
	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class Iter >
	ft::reverse_iterator<Iter>
	operator+( typename ft::reverse_iterator<Iter>::difference_type n,
				const ft::reverse_iterator<Iter>& it )
	{
		return ft::reverse_iterator<Iter>(it.base() - n);
	}

	template< class Iterator >
	typename ft::reverse_iterator<Iterator>::difference_type
	operator-( const ft::reverse_iterator<Iterator>& lhs,
				const ft::reverse_iterator<Iterator>& rhs )
	{
		return rhs.base() - lhs.base();
	}
};

} // namespace ft

#endif
