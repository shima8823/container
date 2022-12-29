#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "pair.hpp"

namespace ft
{

enum _Rb_tree_color { _S_red = false, _S_black = true };

// struct _Rb_tree_node
template<typename _Val>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	typedef _Rb_tree_node<_Val>* _Link_type;

	_Rb_tree_color	_M_color;
	_Link_type		_M_parent;
	_Link_type		_M_left;
	_Link_type		_M_right;

	_Val*			_M_value_type;// debug用

	_Link_type uncle() {
		if (_M_parent == NULL || _M_parent->_M_parent == NULL)
			return NULL;
		if (_M_parent->isOnLeft())
			return _M_parent->_M_parent->_M_right;
		else
			return _M_parent->_M_parent->_M_left;
	}

	bool isOnLeft() {return this == _M_parent->_M_left;}

	_Link_type sibling() {
		if (_M_parent == NULL)
			return NULL;
		if (isOnLeft())
			return _M_parent->_M_right;
		return _M_parent->_M_left;
	}

	void moveDown(_Link_type nParent) {
		if (_M_parent != NULL) {
			if (isOnLeft())
				_M_parent->_M_left = nParent;
			else
				_M_parent->_M_right = nParent;
		}
		nParent->_M_parent = _M_parent;
		_M_parent = nParent;
	}

	bool hasRedChild() {
		return (_M_left != NULL && _M_left->_M_color == _S_red) ||
				(_M_right != NULL && _M_right->_M_color == _S_red);
	}

	template <typename _Val>
	static _Rb_tree_node<_Val>* local_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw()
	{
		//size == 0
		if (__x->_M_right == __x)
			return __x;

		if (__x->_M_right != 0)
		{
			__x = __x->_M_right;
			while (__x->_M_left != 0)
				__x = __x->_M_left;
		}
		else
		{
			_Rb_tree_node<_Val>* __y = __x->_M_parent;
			while (__x == __y->_M_right)
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			if (__x->_M_right != __y)
				__x = __y;
		}
		return __x;
	}

	_Rb_tree_node<_Val>*
	_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw ()
	{
		return local_Rb_tree_increment(__x);
	}

	const _Rb_tree_node<_Val>*
	_Rb_tree_increment(const _Rb_tree_node<_Val>* __x) throw ()
	{
		return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(__x));
	}

	static _Rb_tree_node<_Val>*
	local_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
	{
		//size == 0
		if (__x->_M_right == __x)
			return __x;
		
		if (__x->_M_color == _S_red
			&& __x->_M_parent->_M_parent == __x)
			__x = __x->_M_right;
		else if (__x->_M_left != 0)
		{
			_Rb_tree_node<_Val>* __y = __x->_M_left;
			while (__y->_M_right != 0)
				__y = __y->_M_right;
			__x = __y;
		}
		else
		{
			_Rb_tree_node<_Val>* __y = __x->_M_parent;
			while (__x == __y->_M_left)
			{
				__x = __y;
				__y = __y->_M_parent;
			}
			__x = __y;
		}
		return __x;
	}

	_Rb_tree_node<_Val>*
	_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
	{
		return local_Rb_tree_decrement(__x);
	}

	const _Rb_tree_node<_Val>*
	_Rb_tree_decrement(const _Rb_tree_node<_Val>* __x) throw ()
	{
		return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(__x));
	}
};

// struct _Rb_tree_iterator
template<typename _Tp>
struct _Rb_tree_iterator
{
	typedef _Tp  value_type;
	typedef _Tp& reference;
	typedef _Tp* pointer;

	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_iterator<_Tp>		_Self;
	typedef typename _Rb_tree_node<_Tp>::_Link_type	_Link_type;

	_Rb_tree_iterator() : _M_node() {}

	explicit
	_Rb_tree_iterator(_Link_type __x) : _M_node(__x) { }

	reference operator*() const {return *_M_node->_M_value_type;}
	pointer operator->() const {return _M_node->_M_value_type;}

	_Self& operator++() {
		_M_node = _Rb_tree_increment(_M_node);
		return *this;
	}

	_Self operator++(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_increment(_M_node);
		return __tmp;
	}

	_Self& operator--() {
		_M_node = _Rb_tree_decrement(_M_node);
		return *this;
	}

	_Self operator--(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_decrement(_M_node);
		return __tmp;
	}

	bool operator==(const _Self& __x, const _Self& __y) {
		return __x._M_node == __y._M_node;
	}

	// operator!=

	_Link_type _M_node;
};

// struct _Rb_tree_const_iterator
template<typename _Tp>
struct _Rb_tree_const_iterator
{
	typedef _Tp	 value_type;
	typedef const _Tp& reference;
	typedef const _Tp* pointer;

	typedef _Rb_tree_iterator<_Tp> iterator;

	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_const_iterator<_Tp>		_Self;
	typedef const _Rb_tree_node<_Tp>::_Link_type	_Link_type;

	_Rb_tree_const_iterator() : _M_node() { }

	explicit _Rb_tree_const_iterator(_Link_type __x) : _M_node(__x) { }

	_Rb_tree_const_iterator(const iterator& __it) : _M_node(__it._M_node) { }

	iterator _M_const_cast() const {
		return iterator(const_cast<typename iterator::_Link_type>(_M_node));
	}

	reference operator*() const {return *_M_node->_M_value_type;}
	pointer operator->() const {return _M_node->_M_value_type;}

	_Self& operator++() {
		_M_node = _Rb_tree_increment(_M_node);
		return *this;
	}

	_Self operator++(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_increment(_M_node);
		return __tmp;
	}

	_Self& operator--() {
		_M_node = _Rb_tree_decrement(_M_node);
		return *this;
	}

	_Self operator--(int) {
		_Self __tmp = *this;
		_M_node = _Rb_tree_decrement(_M_node);
		return __tmp;
	}

	bool operator==(const _Self& __x, const _Self& __y) {
		return __x._M_node == __y._M_node;
	}

	// operator!=

	_Link_type _M_node;
};

// class _Rb_tree
template<typename _Key, typename _Val, typename _KeyOfValue,
		typename _Compare, typename _Alloc = std::allocator<_Val> >
class _Rb_tree
{
	typedef typename _Alloc::template
		rebind<_Rb_tree_node<_Val> >::other _Node_allocator;
	// typedef __gnu_cxx::__alloc_traits<_Node_allocator> _Alloc_traits;

	// Mem
protected:
	typedef _Rb_tree_node<_Val>* 		_Link_type;
	typedef const _Rb_tree_node<_Val>*	_Const_Link_type;
public:
	typedef _Key 				key_type;
	typedef _Val 				value_type;
	typedef value_type* 			pointer;
	typedef const value_type* 		const_pointer;
	typedef value_type& 			reference;
	typedef const value_type& 		const_reference;
	typedef size_t 				size_type;
	typedef ptrdiff_t 			difference_type;
	typedef _Alloc 				allocator_type;
	// compare

// original
private:
	_Link_type _M_header;
	size_type _M_node_count;
	key_compare _M_key_compare;
	_Node_allocator _M_node_alloc;


public:
	typedef _Rb_tree_iterator<value_type>       iterator;
	typedef _Rb_tree_const_iterator<value_type> const_iterator;
	typedef ft::reverse_iterator<iterator>       reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

// myhelper 

protected:
	key_type _S_key(_Link_type x) const {return x->_M_value_type->first;}
	key_type _S_key(_Const_Link_type x) const {return x->_M_value_type->first;}
	key_type _S_key(value_type x) const {return x.first;}
	key_type _S_key(iterator x) const {return x->first;}
	key_type _S_key(const_iterator x) const {return x->first;}
	_Link_type _M_end() {return _M_header;}
	_Const_Link_type _M_end() const {return _M_header;}
	_Link_type _S_root() {return _M_header->_M_parent;}
	_Const_Link_type _S_root() const {return _M_header->_M_parent;}
	_Link_type& _M_root() {return _M_header->_M_parent;}
	_Const_Link_type _M_root() const {return _M_header->_M_parent;}

	_Link_type _S_mostleft() {
		_Link_type ret = _S_root();
		if (ret == NULL)
			return _M_header;
		while (ret->_M_left)
			ret = ret->_M_left;
		return ret;
	}
	_Const_Link_type _S_mostleft() const {
		return (_Const_Link_type)_S_mostleft();
	}
	_Link_type _S_mostright() {
		_Link_type ret = _S_root();
		if (ret == NULL)
			return _M_header;
		while (ret->_M_right)
			ret = ret->_M_right;
		return ret;
	}
	_Const_Link_type _S_mostright() const {
		return (_Const_Link_type)_S_mostright();
	}

	void _M_reset() {
		_M_header->_M_color = _S_red;
		_M_header._M_parent = 0;
		_M_header._M_left = &_M_header;
		_M_header._M_right = &_M_header;
		_M_node_count = 0;
	}

	void _M_move_data(_Rb_tree& __from) {
		_M_header._M_color = __from._M_header._M_color;
		_M_header._M_parent = __from._M_header._M_parent;
		_M_header._M_left = __from._M_header._M_left;
		_M_header._M_right = __from._M_header._M_right;
		_M_header._M_parent->_M_parent = _M_header;
		_M_node_count = __from._M_node_count;
		__from._M_reset();
	}

	//// iterator

public:
	iterator begin() {return iterator(_M_header->_M_left);}
	const_iterator begin() const {return const_iterator(_M_header->_M_left);}
	iterator end() {return iterator(_M_header);}
	const_iterator end() const {return const_iterator(_M_header);}

	reverse_iterator rbegin() {return reverse_iterator(end());}
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
	reverse_iterator rend() {return reverse_iterator(begin());}
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
	
	bool empty() const {return _M_node_count == 0;}
	size_type size() const {return _M_node_count;}

	//// insert

protected:
	_Link_type BSTInsert(_Link_type root, _Link_type pt) {
		if (root == NULL)
			return pt;

		if (_M_key_compare(_S_key(pt), _S_key(root))) {
			root->_M_left = BSTInsert(root->_M_left, pt);
			root->_M_left->_M_parent = root;
		} else if (_M_key_compare(_S_key(root), _S_key(pt))) {
			root->_M_right = BSTInsert(root->_M_right, pt);
			root->_M_right->_M_parent = root;
		}

		return root;
	}

	void leftRotate(_Link_type x) {
		_Link_type nParent = x->_M_right;

		if (x == _S_root())
			_M_root() = nParent;

		x->moveDown(nParent);

		x->_M_right = nParent->_M_left;

		if (nParent->_M_left != NULL)
			nParent->_M_left->_M_parent = x;
		
		nParent->_M_left = x;
	}
	
	void rightRotate(_Link_type x) {
		_Link_type nParent = x->_M_left;

		if (x == _S_root())
			_M_root() = nParent;

		x->moveDown(nParent);

		x->_M_left = nParent->_M_right;

		if (nParent->_M_right != NULL)
			nParent->_M_right->_M_parent = x;
		
		nParent->_M_right = x;
	}

	void fixRedRed(_Link_type& pt) {
		_Link_type parent_pt = NULL;
		_Link_type grand_parent_pt = NULL;

		while ((pt != _S_root()) && (pt->_M_color != _S_black) &&
				(pt->_M_parent->_M_color == _S_red))
		{
			parent_pt = pt->_M_parent;
			grand_parent_pt = pt->_M_parent->_M_parent;

			if (parent_pt == grand_parent_pt->_M_left) {
				_Link_type uncle_pt = grand_parent_pt->_M_right;
			
				if (uncle_pt != NULL && uncle_pt->_Mcolor == _S_red) {
					grand_parent_pt->_M_color = _S_red;
					parent_pt->_M_color = _S_black;
					uncle_pt-> _M_color = _S_black;
					pt = grand_parent_pt;
				} else {
					if (pt == parent_pt->_M_right) {
						leftRotate(parent_pt);
						pt = parent_pt;
						parent_pt = pt->_M_parent;
					}

					rightRotate(grand_parent_pt);
					std::swap(parent_pt->_M_color, grand_parent_pt->_M_color);
					pt = parent_pt;
				}
			} else {
				_Link_type uncle_pt = grand_parent_pt->_M_left;

				if (uncle_pt != NULL && uncle_pt->_Mcolor == _S_red) {
					grand_parent_pt->_M_color = _S_red;
					parent_pt->_M_color = _S_black;
					uncle_pt-> _M_color = _S_black;
					pt = grand_parent_pt;
				} else {
					if (pt == parent_pt->_M_left) {
						rightRotate(parent_pt);
						pt = parent_pt;
						parent_pt = pt->_M_parent;
					}

					leftRotate(grand_parent_pt);
					std::swap(parent_pt->_M_color, grand_parent_pt->_M_color);
					pt = parent_pt;
				}
			}
		}
		
		_M_root()->_M_color = _S_black;
	}

public:
	ft::pair<iterator, bool> insert(const value_type& x) {
		ft::pair<iterator, bool> ret;

		iterator it = lower_bound(_S_key(x));
		if (it != end() && !_M_key_compare(_S_key(x), _S_key(it))) {
			ret.first == it;
			ret.second = false;
			return ret;
		}

		_Link_type pt = _M_create_node(x);
		_Link_type old = pt;

		_M_root() = BSTInsert(_S_root(), pt);

		fixRedRed(pt);

		_M_root()->_M_parent = _M_header;

		_M_header->_M_left = _S_mostleft();
		_M_header->_M_right = _S_mostright();

		ret.first = (iterator)old;
		ret.second = true;
		return ret;
	}

	//// node helper (_M_xxx)

protected:
	_Link_type _M_get_node() {
		++_M_node_count;
		return _M_node_alloc.allocate(1);
	}

	void _M_put_node(_Link_type p) {
		--_M_node_count;
		_Alloc value_alloc;
		value_alloc.destroy(p->_M_value_type);
		value_alloc.deallocate(p->_M_value_type, 2);
		_M_node_alloc.destroy(p);
		_M_node_alloc.deallocate(p, 1);
	}

	void _M_construct_node(_Link_type node, const value_type& x) {
		try {
			node->_M_color = _S_red;
			node->_M_left = NULL;
			node->_M_right = NULL;
			node->_M_parent = NULL;
			_Alloc value_alloc;
			typename _Alloc::pointer p = value_alloc.allocate(1);
			value_alloc.contruct(p, x);
			node->_M_value_type = p;
		} catch (...) {
			_M_put_node(node);
			throw;
		}
	}

	_Link_type _M_create_node(const value_type& x) {
		_Link_type tmp = _M_get_node();
		_M_construct_node(tmp, x);
		return tmp;
	}

	//// lower_bound

	iterator _M_lower_bound(_Link_type x, _Link_type y, const _Key& k) {
		while (x != 0)
			if (!_M_key_compare(_S_key(x), k))
				y = x, x= x->_M_left;
			else
				x = x->_M_right;
		return iterator(y);
	}

	const_iterator _M_lower_bound(_Link_type x, _Link_type y, const _Key& k) const {
		while (x != 0)
			if (!_M_key_compare(_S_key(x), k))
				y = x, x= x->_M_left;
			else
				x = x->_M_right;
		return iterator(y);
	}

	void _M_erase(_Link_type x) {
		while (x!= 0) {
			_M_erase(x->_M_right);
			_Link_type y = x->_M_left;
			_M_put_node(x);
			x = y;
		}
	}

	iterator lower_bound(const key_type& k) {
		return _M_lower_bound(_S_root(), _M_end(), k);
	}

	const_iterator lower_bound(const key_type& k) const {
		return _M_lower_bound(_S_root(), _M_end(), k);
	}
};

} // namespace ft

#endif
