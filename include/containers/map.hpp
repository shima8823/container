#ifndef MAP_HPP
#define MAP_HPP

#include <tree.hpp>
#include <stl_function.hpp>

namespace ft
{

template<class Key, class T,
		 class Compare = std::less<Key>,
		 class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key						key_type;
	typedef T						mapped_type;
	typedef ft::pair<const Key, T>	value_type;
	typedef Compare					key_compare;
	typedef Allocator				allocator_type;

	//Member classes

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}
	public:
		bool operator()( const value_type& lhs, const value_type& rhs ) const {
			return comp(lhs.first, rhs.first);
		}
	};




private:
	typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, key_compare, allocator_type> _Rep_type;
	_Rep_type _M_t;

public:
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename _Rep_type::iterator				iterator;
	typedef typename _Rep_type::const_iterator			const_iterator;
	typedef typename _Rep_type::size_type				size_type;
	typedef typename _Rep_type::difference_type			difference_type;
	typedef typename _Rep_type::reverse_iterator		reverse_iterator;
	typedef typename _Rep_type::const_reverse_iterator	const_reverse_iterator;

	map() : _M_t() {}

	// Iterators

	iterator begin() { return _M_t.begin(); }
	const_iterator begin() const {return _M_t.begin();}
	iterator end() {return _M_t.end();}
	const_iterator end() const {return _M_t.end();}
	reverse_iterator rbegin() {return _M_t.rbegin();}
	const_reverse_iterator rbegin() const {return _M_t.rbegin();}
	reverse_iterator rend() {return _M_t.rend();}
	const_reverse_iterator rend() const {return _M_t.rend();}

	// Capacity

	bool empty() const {return _M_t.empty();}
	size_type size() const {return _M_t.size();}

	// Modifiers

	ft::pair<iterator,bool> insert (const value_type& val) {return _M_t._M_insert_unique(val);}

	// size_type erase(const key_type& key) { return _M_t.erase(key); }

	// Lookup

	iterator lower_bound (const key_type& k) {
		return _M_t.lower_bound(k);
	}
	const_iterator lower_bound (const key_type& k) const {
		return _M_t.lower_bound(k);
	}
};

} // namespace ft



#endif
