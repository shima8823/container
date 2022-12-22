#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include <algorithm.hpp>
#include <iterator.hpp>
#include <wrap_iter.hpp>
#include <reverse_iterator.hpp>
#include <type_traits.hpp>

namespace ft {

template < typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef T					value_type;
	typedef T*					pointer;
	typedef const pointer		const_pointer;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef Allocator			allocator_type;
	typedef std::size_t			size_type;
	typedef std::ptrdiff_t		difference_type;

	typedef ft::wrap_iter<value_type>	iterator;
	typedef ft::wrap_iter<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// constructor

	vector( ) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(allocator_type()) {}
	vector(const allocator_type &alloc) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {}
	explicit vector(size_type size, const T& value = T(), const Allocator& alloc = Allocator())
		 : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc) {resize(size, value);}
	
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const Allocator &alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		 : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(alloc)
	{
		reserve(std::distance(first, last));
		for (pointer i = first; i != last; ++i)
			push_back(*i);
	}

	// copy

	vector(const vector &r) : _first(NULL), _last(NULL), _reserved_last(NULL), _alloc(r.alloc) {
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
		if (this == &r)
			return *this;
		if (size() == r.size())
			std::copy(r.begin(), r.end(), begin());
		else {
			if (capacity() >= r.size()) {
				std::copy(r.begin(), r.begin() + r.size(), begin()); //?
				for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++_last)
					construct(_last, *src_iter);
			}
			else {
				destroy_until(rbegin()); //?
				reserve(r.size());
				for (const_iterator src_iter = r.begin(), src_end = r.end(), dest_iter = begin(); src_iter != src_end; ++src_iter, ++dest_iter, ++_last)
					construct(dest_iter, *src_iter);
			}
		}
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
			std::fill_n(_first, count, value);
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

	// Capacity

	size_type size() const { return end() - begin(); }
	bool empty() const { return begin() == end(); }
	size_type capacity() const { return _reserved_last - _first; }

	// Modifiers

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

	// Element access

	reference operator[](size_type i) { return _first[i]; }
	const_reference operator[](size_type i) const { return _first[i]; }

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

	reference front() { return *_first; }
	const_reference front() const { return *_first; }
	reference back() { return *(_last - 1); }
	const_reference back() const { return *(_last - 1); }

	pointer data() { return _first; }
	const_pointer data() const { return _first; }

	// Iterators

	iterator begin() { return _first; };
	iterator end() { return _last; };
	const_iterator begin() const { return _first; };
	const_iterator end() const { return _last; };
	reverse_iterator rbegin() { return reverse_iterator(_last); }
	reverse_iterator rend() { return reverse_iterator(_first); }
	const_reverse_iterator rbegin() const { return reverse_iterator(_last); }
	const_reverse_iterator rend() const { return reverse_iterator(_first); }
	
	// Modifiers2

	void clear() { destroy_until(rend()); }
	
	// Capacity2

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
			construct(_last, std::move(*old_iter));
		
		for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); riter != rend; ++riter)
			destroy(&*riter);
		_alloc.deallocate(old_first, old_capacity);
	}

	// Modifiers3

	void resize(size_type sz) {
		if (sz < size()) {
			difference_type diff = size() - sz;
			destroy_until(rbegin() + diff);
			_last = _first + sz;
		} else if (sz > size()) {
			reserve(sz);
			for (; _last != _reserved_last; ++_last)
				construct(_last);
		}
	}
	void resize(size_type sz, const_reference value) {
		if (sz < size()) {
			difference_type diff = size() - sz;
			destroy_until(rbegin() + diff);
			_last = _first + sz;
		} else if (sz > size()) {
			reserve(sz);
			for (; _last != _reserved_last; ++_last)
				construct(_last, value);
		}
	}

private:
	pointer _first;
	pointer _last;
	pointer _reserved_last;
	allocator_type _alloc;

	pointer allocate(size_type n) { return _alloc.allocate(n); }
	void deallocate() { _alloc.deallocate(_first, capacity()); }

	void construct(pointer ptr) { _alloc.construct(ptr, 0); }
	void construct(pointer ptr, const_reference value) { _alloc.construct(ptr, value); }
	void destroy(pointer ptr) { _alloc.destroy(ptr); }
	void destroy_until(reverse_iterator rend) {
		for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --_last)
			destroy(&*riter);
	}
};
} // namespace ft

#endif
