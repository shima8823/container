#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm.hpp>
#include <iterator.hpp>
#include <wrap_iter.hpp>
#include <reverse_iterator.hpp>
#include <type_traits.hpp>

#include <iostream>
#include <iterator> // std::distance

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef T										value_type;
	typedef Allocator								allocator_type;
	typedef typename allocator_type::pointer		pointer;
	typedef typename allocator_type::const_pointer	const_pointer;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef std::size_t								size_type;
	typedef std::ptrdiff_t							difference_type;

	typedef ft::wrap_iter<pointer>					iterator;
	typedef ft::wrap_iter<const_pointer>			const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	// constructor

	vector( ) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(allocator_type()) {}

	explicit vector(const allocator_type &alloc) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {}

	explicit vector(size_type size, const T& value = T(), const Allocator& alloc = Allocator())
		 : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc)
	{resize(size, value);}
	
	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const Allocator &alloc = Allocator(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		 : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc)
	{
		reserve(std::distance(first, last));
		for (InputIterator i = first; i != last; ++i)
			push_back(*i);
	}

	vector(const vector &r) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(r._alloc) {
		reserve(r.size());
		pointer dest = _first;
		for (const_iterator src = r.begin(), _last = r.end(); src != _last; ++dest, ++src)
			construct(dest, *src);
		_last = _first + r.size();
	}

	// destructor

	~vector() {
		clear();
		deallocate();
	}
	
	vector &operator=(const vector &r) {
		if (this == &r) return *this;
		assign(r.begin(), r.end());
		return *this;
	}

	void assign( size_type count, const T& value ) {
		if (count > capacity()) {
			clear();
			reserve(count);
			std::uninitialized_fill_n(_first, count, value);
		} else {
			size_type sz = size();
			if (count < sz)
				destroy_until(rbegin() + (sz - count));
			std::uninitialized_fill_n(_first, count, value);
		}
		_last = _first + count;
	}

	template< class InputIt >
	void assign(InputIt first, InputIt last,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
		size_type new_size = static_cast<size_type>(std::distance(first, last));
		if (new_size > capacity())
		{
			clear();
			reserve(new_size);
			std::uninitialized_copy(first, last, _first);
		}
		else
		{
			size_type sz = size();
			if (new_size < sz)
				destroy_until(rbegin() + (sz - new_size));
			std::uninitialized_copy(first, last, _first);
		}
		_last = _first + new_size;
	}

	allocator_type get_allocator() const { return _alloc; }

	// Element access

	reference at(size_type i) {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return _first[i];
	}

	const_reference at(size_type i) const {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return _first[i];
	}

	reference operator[](size_type i) { return _first[i]; }
	const_reference operator[](size_type i) const { return _first[i]; }

	reference front() { return *_first; }
	const_reference front() const { return *_first; }
	reference back() { return *(_last - 1); }
	const_reference back() const { return *(_last - 1); }

	pointer data() { return _first; }
	const_pointer data() const { return _first; }

	// Iterators

	iterator begin() { return iterator(_first); };
	iterator end() { return iterator(_last); };
	const_iterator begin() const { return const_iterator(_first); };
	const_iterator end() const { return const_iterator(_last); };
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	// Capacity

	bool empty() const { return begin() == end(); }
	size_type size() const { return end() - begin(); }

	size_type max_size() const {
		return std::min<size_type>(_alloc.max_size(),
				std::numeric_limits<difference_type>::max());
	}

	void reserve(size_type sz) {
		if (sz <= capacity())
			return ;
		pointer ptr = allocate(sz);

		pointer old_first = _first;
		pointer old_last = _last;
		size_type old_capacity = capacity();

		_first = ptr;
		_last = _first;
		_reserved_last = _first + sz;

		for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++_last)
			construct(_last, *old_iter);
		
		for (reverse_iterator riter = reverse_iterator((wrap_iter<pointer>)old_last),
							  rend = reverse_iterator((wrap_iter<pointer>)old_first);
							  riter != rend;
							  ++riter)
			destroy(&*riter);
		_alloc.deallocate(old_first, old_capacity);
	}

	size_type capacity() const { return _reserved_last - _first; }

	// Modifiers

	void clear() { destroy_until(rend()); }

	iterator insert( iterator pos, const T& value ){
		difference_type offset = pos - begin();
		insert(pos, 1, value);
		return begin() + offset;
	}

	void insert( iterator pos, size_type count, const T& value ) {
		if (count == 0) return;
		difference_type	offset = pos - begin();
		size_type		new_size = size() + count;
		if (new_size > capacity())
			reserve(recommend(new_size));
		pointer new_pos = _first + offset;
		// 未初期化のもの埋めていく。_lastもずらす。
		if (new_size > size()) {
			std::uninitialized_fill_n(_last, new_size - size(), value);
			_last += new_size - size();
		}
		// new_pos ~ _last - count を _last に 後ろから詰めていく。
		// イメージはtest_vectorの335 から337がいい例。
		std::copy_backward(new_pos, _last - count, _last);
		// new_pos ~ new_pos + count まで valueで詰める。
		std::fill(new_pos, new_pos + count, value);
	}

	template< class InputIt >
	typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
	insert( iterator pos, InputIt first, InputIt last ){
		difference_type count = std::distance(first, last);
		if (count == 0) return;
		difference_type	offset = pos - begin();
		size_type		new_size = size() + count;
		if (new_size > capacity())
			reserve(recommend(new_size));
		pointer new_pos = _first + offset;
		if (new_size > size()) {
			std::uninitialized_fill_n(_last, new_size - size(), *first);
			_last += new_size - size();
		}
		std::copy_backward(new_pos, _last - count, _last);
		std::copy(first, last, new_pos);
	}

	iterator erase( iterator pos ) {
		return erase(pos, pos + 1);
	}

	// 42, 21, -21, -42
	// first = begin() + 1, last = begin() + 2;
	// 42, -21, -42
	iterator erase( iterator first, iterator last ) {
		difference_type erase_size = std::distance(first, last);
		if (first != last) {
			if (last != end())
				std::copy(last, end(), first);
			destroy_until(rbegin() + erase_size);
		}
		return first;
	}

	void push_back(const_reference value) {
		if (size() + 1 > capacity()) {
			size_type c = size();
			if (c == 0)
				c = 1;
			else
				c *= 2;
			reserve(c);
		}
		construct(_last, value);
		++_last;
	}

	void pop_back() {destroy_until(rbegin() + 1);}

	void resize(size_type count, value_type value = T()) {
		if (count < size())
			erase(begin() + count, end());
		else if (count > size())
			insert(end(), count - size(), value);
	}

	void swap( vector& other ) {
		pointer tmp_first = other._first;
		pointer tmp_last = other._last;
		pointer tmp_reserved_last = other._reserved_last;
		allocator_type tmp_alloc = other._alloc;

		other._first = this->_first;
		other._last = this->_last;
		other._reserved_last = this->_reserved_last;
		other._alloc = this->_alloc;

		this->_first = tmp_first;
		this->_last = tmp_last;
		this->_reserved_last = tmp_reserved_last;
		this->_alloc = tmp_alloc;
	}

protected:
	pointer _first;
	pointer _last;
	pointer _reserved_last;
	allocator_type _alloc;

private:
	pointer allocate(size_type n) { return _alloc.allocate(n); }
	void deallocate() { _alloc.deallocate(_first, capacity()); }

	void construct(pointer ptr, const_reference value) { _alloc.construct(ptr, value); }
	void destroy(pointer ptr) { _alloc.destroy(ptr); }
	void destroy_until(reverse_iterator rend) {
		for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --_last)
			destroy(&*riter);
	}

	size_type recommend(size_type new_size) const {
		const size_type ms = max_size();
		if (new_size > ms)
			throw std::length_error("too long size");
		const size_type cap = capacity();
		if (cap >= ms / 2)
			return ms;
		return std::max<size_type>(2 * cap, new_size);
	}
};

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return !(rhs < lhs);
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
	return rhs < lhs;
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
	return !(lhs < rhs);
}

} // namespace ft

namespace std
{

template< class T, class Alloc >
void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
	lhs.swap(rhs);
}

} // namespace std


#endif
