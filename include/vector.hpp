#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template < typename T, typename Allocator = std::allocator<T> >
class vector
{
private:
	pointer first;
	pointer last;
	pointer reserved_last;
	allocator_type alloc;
public:
	using value_type		= T;
	using pointer			= T*;
	using const_pointer		= const pointer;
	using reference			= value_type &;
	using const_reference	= const value_type &;
	using allocator_type	= Allocator;
	using size_type			= std::size_t;

	// イテレーターのエイリアス
	using iterator = pointer;
	using const_iterator = const_pointer;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	vector( std::size_t n = 0, Allocator a = Allocator() );
	~vector();
	vector( const vector &x);
	vector &operator=(const vector &x);

	// 要素アクセス
	void push_back(const T &x);
	T &operator[](std::size_t i) noexcept;

	// イテレーターアクセス
	iterator begin() noexcept { return first; };
	iterator end() noexcept { return last; };
	iterator begin() const noexcept { return first; };
	iterator end() const noexcept { return last; };
	const_iterator cbegin() const noexcept { return first; };
	const_iterator cend() const noexcept { return last; };
	reverse_iterator rbegin() noexcept { return reverse_iterator{ last }; }
	reverse_iterator rend() noexcept { return reverse_iterator{ first }; }
	const_reverse_iterator crbegin() const noexcept { return reverse_iterator{ last }; }
	const_reverse_iterator crend() const noexcept { return reverse_iterator{ first }; }

	size_type size() const noexcept { return end() - begin(); }
	bool empty() const noexcept { return size() == 0; }
	size_type capacity() const noexcept { return reserved_last - first; }

	reference operator[](size_type i) { return first[i]; }
	const_reference operator[](size_type i) const { return first[i]; }

	reference at(size_type i) {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return first[i];
	}
	const reference at(size_type i) const {
		if (i >= size())
			throw std::out_of_range("index is out of range.");
		return first[i];
	}

	reference front() { return first; }
	const_reference front() const { return first; }
	reference back() { return last - 1; }
	const_reference back() const { return last - 1; }

	pointer data() noexcept { return first; }
	const_pointer data() noexcept const { return first; }

};

#endif
