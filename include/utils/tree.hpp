#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "pair.hpp"

namespace ft
{

enum _Rb_tree_color { _S_red = false, _S_black = true };

/*--------------------------------------------------------------------------*/
/*                               _Rb_tree_node                              */
/*--------------------------------------------------------------------------*/

template<typename _Val>
struct _Rb_tree_node
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
};

/*--------------------------------------------------------------------------*/
/*                               tree.cc                                    */
/*--------------------------------------------------------------------------*/

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

template <typename _Val>
_Rb_tree_node<_Val>*
_Rb_tree_increment(_Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_increment(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>*
_Rb_tree_increment(const _Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_increment(const_cast<_Rb_tree_node<_Val>*>(__x));
}

template <typename _Val>
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

template <typename _Val>
_Rb_tree_node<_Val>*
_Rb_tree_decrement(_Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_decrement(__x);
}

template <typename _Val>
const _Rb_tree_node<_Val>*
_Rb_tree_decrement(const _Rb_tree_node<_Val>* __x) throw ()
{
	return local_Rb_tree_decrement(const_cast<_Rb_tree_node<_Val>*>(__x));
}

/*--------------------------------------------------------------------------*/
/*                             _Rb_tree_iterator                            */
/*--------------------------------------------------------------------------*/

template<typename _Tp>
struct _Rb_tree_iterator
{
	typedef _Tp  value_type;
	typedef _Tp& reference;
	typedef _Tp* pointer;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_iterator<_Tp>		_Self;
	typedef typename _Rb_tree_node<_Tp>::_Link_type	_Link_type;

	_Link_type _M_node;

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

	bool operator==(const _Self& __x) {
		return _M_node == __x._M_node;
	}

	bool operator!=(const _Self& __x) {
		return _M_node != __x._M_node;
	}
};

/*--------------------------------------------------------------------------*/
/*                          _Rb_tree_const_iterator                         */
/*--------------------------------------------------------------------------*/

template<typename _Tp>
struct _Rb_tree_const_iterator
{
	typedef _Tp	 value_type;
	typedef const _Tp& reference;
	typedef const _Tp* pointer;

	typedef _Rb_tree_iterator<_Tp> iterator;

	typedef std::bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t			 difference_type;

	typedef _Rb_tree_const_iterator<_Tp>		_Self;
	typedef const _Rb_tree_node<_Tp>*			_Link_type;

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

	bool operator==(const _Self& __x) {
		return _M_node == __x._M_node;
	}

	bool operator!=(const _Self& __x) {
		return _M_node != __x._M_node;
	}

	_Link_type _M_node;
};

/*--------------------------------------------------------------------------*/
/*                                 _Rb_tree                                 */
/*--------------------------------------------------------------------------*/

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
	typedef _Compare key_compare; // _Compareのタイプ

  // _Rb_tree_impl
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

  public:
	_Rb_tree() : _M_key_compare(key_compare()), _M_node_alloc(_Node_allocator()) {
		_M_header = _M_create_node(value_type());
		_M_reset();
	}
	~_Rb_tree() {
		clear();
		_M_drop_node(_M_header);
	}

  // myhelper 

  protected:
  //setなのでいらない？_S_
	key_type _S_key(_Link_type x) const {return x->_M_value_type->first;}
	key_type _S_key(_Const_Link_type x) const {return x->_M_value_type->first;}
	key_type _S_key(value_type x) const {return x.first;}
	key_type _S_key(iterator x) const {return x->first;}
	key_type _S_key(const_iterator x) const {return x->first;}

	_Link_type _M_end() {return _M_header;}
	_Const_Link_type _M_end() const {return _M_header;}
	// _S_root 意味ある？
	_Link_type _S_root() {return _M_header->_M_parent;}
	_Const_Link_type _S_root() const {return _M_header->_M_parent;}
	_Link_type& _M_root() {return _M_header->_M_parent;}
	_Const_Link_type _M_root() const {return _M_header->_M_parent;}

	_Link_type _M_begin() { return _M_header->_M_parent; }

	static _Link_type _S_right(_Link_type __x) {return __x->_M_right;}
	static _Link_type _S_left(_Link_type __x) {return __x->_M_left;}

	// most系はgccに存在しないので変更
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

	static _Link_type _S_minimum(_Link_type __x) {
		while (__x->_M_left != 0)
			__x = __x->_M_left;
		return __x;
	}

	static _Link_type _S_maximum(_Link_type __x) {
		while (__x->_M_right != 0)
			__x = __x->_M_right;
		return __x;
	}

	//_Rb_tree_header

	void _M_reset() {
		_M_header->_M_color = _S_red;
		_M_header->_M_parent = 0;
		_M_header->_M_left = _M_header;
		_M_header->_M_right = _M_header;
		_M_node_count = 0;
	}

	// void _M_move_data(_Rb_tree& __from) {
	// 	_M_header._M_color = __from._M_header._M_color;
	// 	_M_header._M_parent = __from._M_header._M_parent;
	// 	_M_header._M_left = __from._M_header._M_left;
	// 	_M_header._M_right = __from._M_header._M_right;
	// 	_M_header._M_parent->_M_parent = _M_header;
	// 	_M_node_count = __from._M_node_count;
	// 	__from._M_reset();
	// }

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

	ft::pair<_Link_type, _Link_type> _M_get_insert_unique_pos(const key_type &__k) {
		typedef pair<_Link_type, _Link_type> _Res;
		_Link_type __x = _S_root();
		_Link_type __y = _M_end();
		bool __comp = true;
		while (__x != 0) {
			__y = __x;
			__comp = _M_key_compare(__k, _S_key(__x));
			__x = __comp ? __x->_M_left : __x->_M_right;
		}
		iterator __j = iterator(__y);
		if (__comp) {
			if (__j == begin())
				return _Res(__x, __y);
			else
				--__j;
		}
		if (_M_key_compare(_S_key(__j._M_node), __k))
			return _Res(__x, __y);
		return _Res(__j._M_node, 0);
	}

	static void local_Rb_tree_rotate_right(_Link_type const __x,
										_Link_type& __root) {
		_Link_type const __y = __x->_M_left;

		__x->_M_left = __y->_M_right;
		if (__y->_M_right != 0)
		__y->_M_right->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
		__root = __y;
		else if (__x == __x->_M_parent->_M_right)
		__x->_M_parent->_M_right = __y;
		else
		__x->_M_parent->_M_left = __y;
		__y->_M_right = __x;
		__x->_M_parent = __y;
	}

	static void local_Rb_tree_rotate_left(_Link_type const __x,
										_Link_type& __root) {
		_Link_type const __y = __x->_M_right;

		__x->_M_right = __y->_M_left;
		if (__y->_M_left !=0)
		__y->_M_left->_M_parent = __x;
		__y->_M_parent = __x->_M_parent;

		if (__x == __root)
		__root = __y;
		else if (__x == __x->_M_parent->_M_left)
		__x->_M_parent->_M_left = __y;
		else
		__x->_M_parent->_M_right = __y;
		__y->_M_left = __x;
		__x->_M_parent = __y;
	}

	void _Rb_tree_insert_and_rebalance(const bool __insert_left,
									_Link_type __x,
									_Link_type __p,
									_Link_type& __header) throw () {
		_Link_type & __root = __header->_M_parent;

		// Initialize fields in new node to insert.
		__x->_M_parent = __p;
		__x->_M_left = 0;
		__x->_M_right = 0;
		__x->_M_color = _S_red;

		// Insert.
		// Make new node child of parent and maintain root, leftmost and
		// rightmost nodes.
		// N.B. First node is always inserted left.
		if (__insert_left) {
			__p->_M_left = __x; // also makes leftmost = __x when __p == &__header

			if (__p == __header) {
				__header->_M_parent = __x;
				__header->_M_right = __x;
			}
			else if (__p == __header->_M_left)
				__header->_M_left = __x; // maintain leftmost pointing to min node
		} else {
			__p->_M_right = __x;

			if (__p == __header->_M_right)
				__header->_M_right = __x; // maintain rightmost pointing to max node
		}
		// Rebalance.
		while (__x != __root && __x->_M_parent->_M_color == _S_red) {
			_Link_type const __xpp = __x->_M_parent->_M_parent;

			if (__x->_M_parent == __xpp->_M_left) {
				_Link_type const __y = __xpp->_M_right;
				if (__y && __y->_M_color == _S_red) {
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				} else {
					if (__x == __x->_M_parent->_M_right) {
						__x = __x->_M_parent;
						local_Rb_tree_rotate_left(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					local_Rb_tree_rotate_right(__xpp, __root);
				}
			} else {
				_Link_type const __y = __xpp->_M_left;
				if (__y && __y->_M_color == _S_red) {
					__x->_M_parent->_M_color = _S_black;
					__y->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					__x = __xpp;
				} else {
					if (__x == __x->_M_parent->_M_left) {
						__x = __x->_M_parent;
						local_Rb_tree_rotate_right(__x, __root);
					}
					__x->_M_parent->_M_color = _S_black;
					__xpp->_M_color = _S_red;
					local_Rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->_M_color = _S_black;
	}

	iterator _M_insert_(_Link_type __x, _Link_type __p, const value_type &__v) {
		bool __insert_left = (__x != 0 || __p == _M_end()
					|| _M_key_compare(_KeyOfValue()(__v), _S_key(__p)));

		_Link_type __z = _M_create_node(__v);

		_Rb_tree_insert_and_rebalance(__insert_left, __z, __p, _M_header);
		++_M_node_count;
		return iterator(__z);
	}

	ft::pair<iterator, bool> _M_insert_unique(const value_type& __v) {
		typedef pair<iterator, bool> _Res;
		pair<_Link_type, _Link_type> __res = _M_get_insert_unique_pos(_KeyOfValue()(__v));
		if (__res.second)
			return _Res(_M_insert_(__res.first, __res.second, __v), true);
		return _Res(iterator(__res.first), false);
	}

	//// erase

	iterator _M_upper_bound(_Link_type __x, _Link_type __y, const _Key& __k) {
		while (__x != 0)
			if (_M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
      return iterator(__y);
	}

	pair<iterator, iterator> equal_range(const _Key& __k)
	{
		_Link_type __x = _M_begin();
		_Link_type __y = _M_end();
		while (__x != 0)
		{
			if (_M_key_compare(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else {
				_Link_type __xu(__x);
				_Link_type __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return pair<iterator,
					iterator>(_M_lower_bound(__x, __y, __k),
							_M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<iterator, iterator>(iterator(__y), iterator(__y));
	}

	_Link_type _Rb_tree_rebalance_for_erase(_Link_type const __z,
			       _Link_type& __header) throw ()
  {
    _Link_type& __root = __header->_M_parent;
    _Link_type& __leftmost = __header->_M_left;
    _Link_type& __rightmost = __header->_M_right;
    _Link_type __y = __z;
    _Link_type __x = 0;
    _Link_type __x_parent = 0;

    if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
      __x = __y->_M_right;     // __x might be null.
    else
      if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
	__x = __y->_M_left;    // __x is not null.
      else
	{
	  // __z has two non-null children.  Set __y to
	  __y = __y->_M_right;   //   __z's successor.  __x might be null.
	  while (__y->_M_left != 0)
	    __y = __y->_M_left;
	  __x = __y->_M_right;
	}
    if (__y != __z)
      {
	// relink y in place of z.  y is z's successor
	__z->_M_left->_M_parent = __y;
	__y->_M_left = __z->_M_left;
	if (__y != __z->_M_right)
	  {
	    __x_parent = __y->_M_parent;
	    if (__x) __x->_M_parent = __y->_M_parent;
	    __y->_M_parent->_M_left = __x;   // __y must be a child of _M_left
	    __y->_M_right = __z->_M_right;
	    __z->_M_right->_M_parent = __y;
	  }
	else
	  __x_parent = __y;
	if (__root == __z)
	  __root = __y;
	else if (__z->_M_parent->_M_left == __z)
	  __z->_M_parent->_M_left = __y;
	else
	  __z->_M_parent->_M_right = __y;
	__y->_M_parent = __z->_M_parent;
	std::swap(__y->_M_color, __z->_M_color);
	__y = __z;
	// __y now points to node to be actually deleted
      }
    else
      {                        // __y == __z
	__x_parent = __y->_M_parent;
	if (__x)
	  __x->_M_parent = __y->_M_parent;
	if (__root == __z)
	  __root = __x;
	else
	  if (__z->_M_parent->_M_left == __z)
	    __z->_M_parent->_M_left = __x;
	  else
	    __z->_M_parent->_M_right = __x;
	if (__leftmost == __z)
	  {
	    if (__z->_M_right == 0)        // __z->_M_left must be null also
	      __leftmost = __z->_M_parent;
	    // makes __leftmost == _M_header if __z == __root
	    else
	      __leftmost = _S_minimum(__x);
	  }
	if (__rightmost == __z)
	  {
	    if (__z->_M_left == 0)         // __z->_M_right must be null also
	      __rightmost = __z->_M_parent;
	    // makes __rightmost == _M_header if __z == __root
	    else                      // __x == __z->_M_left
	      __rightmost = _S_maximum(__x);
	  }
      }
    if (__y->_M_color != _S_red)
      {
	while (__x != __root && (__x == 0 || __x->_M_color == _S_black))
	  if (__x == __x_parent->_M_left)
	    {
	      _Link_type __w = __x_parent->_M_right;
	      if (__w->_M_color == _S_red)
		{
		  __w->_M_color = _S_black;
		  __x_parent->_M_color = _S_red;
		  local_Rb_tree_rotate_left(__x_parent, __root);
		  __w = __x_parent->_M_right;
		}
	      if ((__w->_M_left == 0 ||
		   __w->_M_left->_M_color == _S_black) &&
		  (__w->_M_right == 0 ||
		   __w->_M_right->_M_color == _S_black))
		{
		  __w->_M_color = _S_red;
		  __x = __x_parent;
		  __x_parent = __x_parent->_M_parent;
		}
	      else
		{
		  if (__w->_M_right == 0
		      || __w->_M_right->_M_color == _S_black)
		    {
		      __w->_M_left->_M_color = _S_black;
		      __w->_M_color = _S_red;
		      local_Rb_tree_rotate_right(__w, __root);
		      __w = __x_parent->_M_right;
		    }
		  __w->_M_color = __x_parent->_M_color;
		  __x_parent->_M_color = _S_black;
		  if (__w->_M_right)
		    __w->_M_right->_M_color = _S_black;
		  local_Rb_tree_rotate_left(__x_parent, __root);
		  break;
		}
	    }
	  else
	    {
	      // same as above, with _M_right <-> _M_left.
	      _Link_type __w = __x_parent->_M_left;
	      if (__w->_M_color == _S_red)
		{
		  __w->_M_color = _S_black;
		  __x_parent->_M_color = _S_red;
		  local_Rb_tree_rotate_right(__x_parent, __root);
		  __w = __x_parent->_M_left;
		}
	      if ((__w->_M_right == 0 ||
		   __w->_M_right->_M_color == _S_black) &&
		  (__w->_M_left == 0 ||
		   __w->_M_left->_M_color == _S_black))
		{
		  __w->_M_color = _S_red;
		  __x = __x_parent;
		  __x_parent = __x_parent->_M_parent;
		}
	      else
		{
		  if (__w->_M_left == 0 || __w->_M_left->_M_color == _S_black)
		    {
		      __w->_M_right->_M_color = _S_black;
		      __w->_M_color = _S_red;
		      local_Rb_tree_rotate_left(__w, __root);
		      __w = __x_parent->_M_left;
		    }
		  __w->_M_color = __x_parent->_M_color;
		  __x_parent->_M_color = _S_black;
		  if (__w->_M_left)
		    __w->_M_left->_M_color = _S_black;
		  local_Rb_tree_rotate_right(__x_parent, __root);
		  break;
		}
	    }
	if (__x) __x->_M_color = _S_black;
      }
    return __y;
  }

	void _M_erase_aux(const_iterator __position)
    {
		_Link_type __y = _Rb_tree_rebalance_for_erase(const_cast<_Link_type>(__position._M_node), _M_header);
		_M_drop_node(__y);
		--_M_node_count;
	}

	void _M_erase(_Link_type __x) {
		// Erase without rebalancing.
		while (__x != 0) {
			_M_erase(_S_right(__x));
			_Link_type __y = _S_left(__x);
			_M_drop_node(__x);
			__x = __y;
		}
    }

	void clear() {
		_M_erase(_M_begin());
		_M_reset();
    }

	void _M_erase_aux(const_iterator __first, const_iterator __last) {
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				_M_erase_aux(__first++);
	}

	size_type erase(const key_type& __x) {
		pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		_M_erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	// _Alloc_node 

  protected:
	_Link_type _M_get_node() {
		return _M_node_alloc.allocate(1);
	}

	void _M_destroy_node(_Link_type __p) {
		_Alloc value_alloc;
		value_alloc.destroy(__p->_M_value_type);
		value_alloc.deallocate(__p->_M_value_type, 1);
	}

	void _M_put_node(_Link_type __p) {
		_M_node_alloc.destroy(__p);
		_M_node_alloc.deallocate(__p, 1);
	}

	void _M_drop_node(_Link_type __p) {
		_M_destroy_node(__p);
		_M_put_node(__p);
	}

	// _M_drop_nodeと同じ？
	// void _M_put_node(_Link_type p) {
	// 	--_M_node_count;
	// 	_Alloc value_alloc;
	// 	value_alloc.destroy(p->_M_value_type);
	// 	value_alloc.deallocate(p->_M_value_type, 2);// ?
	// 	_M_node_alloc.destroy(p);
	// 	_M_node_alloc.deallocate(p, 1);
	// }

	void _M_construct_node(_Link_type node, const value_type& x) {
		try {
			node->_M_color = _S_red;
			node->_M_left = NULL;
			node->_M_right = NULL;
			node->_M_parent = NULL;
			_Alloc value_alloc;
			typename _Alloc::pointer p = value_alloc.allocate(1);
			value_alloc.construct(p, x);
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
				x = _S_right(x);
		return iterator(y);
	}

	const_iterator _M_lower_bound(_Link_type x, _Link_type y, const _Key& k) const {
		while (x != 0)
			if (!_M_key_compare(_S_key(x), k))
				y = x, x= x->_M_left;
			else
				x = _S_right(x);
		return iterator(y);
	}

	// _S_root?
	iterator lower_bound(const key_type& k) {
		return _M_lower_bound(_S_root(), _M_end(), k);
	}

	const_iterator lower_bound(const key_type& k) const {
		return _M_lower_bound(_S_root(), _M_end(), k);
	}

};

} // namespace ft

#endif
