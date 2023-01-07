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

	// 比較する関数オブジェクト
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map; // mapからアクセスするため。
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

	// constructor/destructor

	map() : _M_t() {}

	explicit map(const Compare& comp, const Allocator& alloc = Allocator())
		: _M_t(comp, alloc) { }

	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
		: _M_t(comp, alloc) 
	{
		_M_t._M_insert_range_unique(first, last);
	}

	~map() {}

	// copy

	map(const map& other) : _M_t(other._M_t) { }

	map& operator=( const map& other ) {
		if (this == &other)
			return *this;
		_M_t = other._M_t;
		return *this;
	}

	allocator_type get_allocator() const {return allocator_type(_M_t.get_allocator());}

	// Element access

	T& at( const Key& key ) {
		iterator __i = lower_bound(key);
		if (__i == end() || key_comp()(key, (*__i).first))
			throw std::out_of_range("map::at");
		return (*__i).second;
	}

	const T& at( const Key& key ) const {
		const_iterator __i = lower_bound(key);
		if (__i == end() || key_comp()(key, (*__i).first))
			throw std::out_of_range("map::at");
		return (*__i).second;
	}

	T& operator[]( const Key& key ) {
		return insert(ft::make_pair(key, T())).first->second;
	}

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
	size_type max_size() const {return _M_t.max_size();}

	// Modifiers

	void clear() {_M_t.clear();}

	ft::pair<iterator,bool> insert(const value_type& val) {return _M_t._M_insert_unique(val);}
	iterator insert(iterator pos, const value_type& val) {return _M_t._M_insert_unique_(pos, val);}
	template< class InputIt >
	void insert( InputIt first, InputIt last )
	{return _M_t._M_insert_range_unique(first, last);}

	void erase( iterator pos ) {_M_t.erase(pos);}
	void erase( iterator first, iterator last ) {_M_t.erase(first, last);}
	size_type erase(const key_type& key) {return _M_t.erase(key);}

	void swap(map& other) {_M_t.swap(other._M_t);}

	// Lookup

	size_type count(const Key& key) const {return _M_t.find(key) == _M_t.end() ? 0 : 1;}

	iterator find(const Key& key) {return _M_t.find(key);}
	const_iterator find(const Key& key) const {return _M_t.find(key);}

	ft::pair<iterator,iterator> equal_range(const Key& key) {return _M_t.equal_range(key);}
	ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const {return _M_t.equal_range(key);}

	// >=
	iterator lower_bound(const key_type& k) {return _M_t.lower_bound(k);}
	const_iterator lower_bound(const key_type& k) const {return _M_t.lower_bound(k);}

	// <
	iterator upper_bound(const Key& key) {return _M_t.upper_bound(key);}
	const_iterator upper_bound(const Key& key) const {return _M_t.upper_bound(key);}

	// Observers

	key_compare key_comp() const {return _M_t.key_comp();}
	value_compare value_comp() const {return value_compare(_M_t.key_comp());}

};

template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{ return lhs.size() == rhs.size()
	&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{ return !(lhs == rhs); }

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{ return !(rhs < lhs); }

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{ return rhs < lhs; }

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{ return !(lhs < rhs); }

} // namespace ft

namespace std
{

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
	lhs.swap(rhs);
}

}

#endif
