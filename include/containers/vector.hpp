#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include <algorithm.hpp>
#include <iterator.hpp>
#include <wrap_iter.hpp>
#include <reverse_iterator.hpp>

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

	typedef pointer	iterator;
	typedef const_pointer const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	// constructor

	vector( ) : first(NULL), last(NULL), reserved_last(NULL), alloc(allocator_type()) {}
	vector(const allocator_type &alloc) : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {}
	explicit vector(size_type size, const T& value = T(), const Allocator& alloc = Allocator())
		 : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc) {resize(size, value);}
	
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const Allocator &alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		 : first(NULL), last(NULL), reserved_last(NULL), alloc(alloc)
	{
		reserve(std::distance(first, last));
		for (pointer i = first; i != last; ++i)
			push_back(*i);
	}

	// copy

	vector( const vector &r) : first(NULL), last(NULL), reserved_last(NULL), alloc(r.alloc) {
		reserve(r.size());
		for (pointer dest = first, src = r.begin(), last = r.end(); src != last; ++dest, ++src)
			construct(dest, *src);
		last = first + r.size();
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
				for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end(); src_iter != src_end; ++src_iter, ++last)
					construct(last, *src_iter);
			}
			else {
				destroy_until(rbegin()); //?
				reserve(r.size());
				for (const_iterator src_iter = r.begin(), src_end = r.end(), dest_iter = begin(); src_iter != src_end; ++src_iter, ++dest_iter, ++last)
					construct(dest_iter, *src_iter);
			}
		}
		return *this;
	}

	// Capacity

	size_type size() const { return end() - begin(); }
	bool empty() const { return begin() == end(); }
	size_type capacity() const { return reserved_last - first; }

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
		construct(last, value);
		++last;
	}

	// Element access

	reference operator[](size_type i) { return first[i]; }
	const_reference operator[](size_type i) const { return first[i]; }

	reference at(size_type i) {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return first[i];
	}
	const_reference at(size_type i) const {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return first[i];
	}

	reference front() { return *first; }
	const_reference front() const { return *first; }
	reference back() { return *(last - 1); }
	const_reference back() const { return *(last - 1); }

	pointer data() { return first; }
	const_pointer data() const { return first; }

	// Iterators

	iterator begin() { return first; };
	iterator end() { return last; };
	const_iterator begin() const { return first; };
	const_iterator end() const { return last; };
	reverse_iterator rbegin() { return reverse_iterator(last); }
	reverse_iterator rend() { return reverse_iterator(first); }
	const_reverse_iterator rbegin() const { return reverse_iterator(last); }
	const_reverse_iterator rend() const { return reverse_iterator(first); }
	
	// Modifiers2

	void clear() { destroy_until(rend()); }
	
	// Capacity2

	void reserve(size_type sz) {
		if (sz <= capacity())
			return ;
		pointer ptr = allocate(sz);

		pointer old_first = first;
		pointer old_last = last;
		size_type old_capacity = capacity();

		first = ptr;
		last = first;
		reserved_last = first + sz;

		for (pointer old_iter = old_first; old_iter != old_last; ++old_iter, ++last)
			construct(last, std::move(*old_iter));
		
		for (reverse_iterator riter = reverse_iterator(old_last), rend = reverse_iterator(old_first); riter != rend; ++riter)
			destroy(&*riter);
		alloc.deallocate(old_first, old_capacity);
	}

	// Modifiers3

	void resize(size_type sz) {
		if (sz < size()) {
			difference_type diff = size() - sz;
			destroy_until(rbegin() + diff);
			last = first + sz;
		} else if (sz > size()) {
			reserve(sz);
			for (; last != reserved_last; ++last)
				construct(last);
		}
	}
	void resize(size_type sz, const_reference value) {
		if (sz < size()) {
			difference_type diff = size() - sz;
			destroy_until(rbegin() + diff);
			last = first + sz;
		} else if (sz > size()) {
			reserve(sz);
			for (; last != reserved_last; ++last)
				construct(last, value);
		}
	}

private:
	pointer first;
	pointer last;
	pointer reserved_last;
	allocator_type alloc;

	pointer allocate(size_type n) { return alloc.allocate(n); }
	void deallocate() { alloc.deallocate(first, capacity()); }

	void construct(pointer ptr) { alloc.construct(ptr, 0); }
	void construct(pointer ptr, const_reference value) { alloc.construct(ptr, value); }
	void destroy(pointer ptr) { alloc.destroy(ptr); }
	void destroy_until(reverse_iterator rend) {
		for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last)
			destroy(&*riter);
	}
};
} // namespace ft

#endif
