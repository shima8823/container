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

} // namespace ft

#endif
